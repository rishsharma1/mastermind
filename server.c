/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/

/*------------------Libraries---------------------*/
#include "server.h"
/*------------------------------------------------*/



int main(int argc,char * argv[]) {

	struct sockaddr_in server_address, client_address;
	socklen_t len;
	int port_number, clientfd, sockfd;
	default_code = NULL;

	if(argc < NUMBER_OF_ARGUMENTS) {
		fprintf(stderr, "Usage: ./server port_number [default_secert_code]\n");
		exit(EXIT_FAILURE);
	}
	else if(argc == NUMBER_OF_ARGUMENTS + 1) {
		default_code = argv[2];

		if(!is_valid(default_code)) {
			fprintf(stderr, "%s is not a valid code word\n",default_code);
			exit(EXIT_FAILURE);
		}
	}


	/*Initialise the mutex*/
	if(pthread_mutex_init(&lock,NULL) != 0) {
		fprintf(stderr, "Mutex failed to initialise\n");
		exit(EXIT_FAILURE);
	}

	port_number = atoi(argv[1]);
	sockfd = init_server_socket(port_number,&server_address);

	/* new log file */
	fp = fopen(LOG_FILE,"w");

	if(!fp) {
		fprintf(stderr, "Error: Log file failed to create\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);



	/* Set the maximum number of connections, which is 20 in this case*/
	if(listen(sockfd,MAX_CLIENTS) < 0) {
		perror("listen() failed with error");
		exit(EXIT_FAILURE);
	}
	else {
		printf("Listening on port %d....\n",port_number);
	}


	while(TRUE) {


		clientfd = accept(sockfd,(struct sockaddr *)&client_address,&len);

		if(clientfd < 0) {
			perror("Accept failed");
			exit(EXIT_FAILURE);
		}

		/* create the client information data structure for the new client*/
		client_data_t *client_data;
		client_data = (client_data_t *)malloc(sizeof(*client_data));
		assert(client_data != NULL);

		/* initialise the data with information */
		client_data->client_id = clientfd;
		client_data->client_addr = client_address;
		client_data->server_addr = server_address;
		client_data->turns_left = MAX_TURNS;


		/*send rules to client*/
		write(clientfd,RULES,sizeof(RULES));


		/* Create this new thread*/
		pthread_t thread_id;

		if(pthread_create(&thread_id, NULL,play_mastermind,(void *)client_data)) {
			fprintf(stderr, "Failed to create thread.\n");
			exit(EXIT_FAILURE);
		}

		/* Detach this thread */
		if(pthread_detach(thread_id)) {
			fprintf(stderr, "Failed to detach thead.\n");
			exit(EXIT_FAILURE);
		}


	}

	close(server_address);
	return 1;

}

void *play_mastermind(void *data) {

	client_data_t *client_data = (client_data_t *)data;

	int client_fd = client_data->client_id;
	char secret_code[GUESS_LENGTH+1];
	char msg[MESSAGE_LENGTH];
	char guess[CODE_LENGTH+1];
	int player_win = 0,i;



	/*generate a random code word or use default if provided*/
	if(default_code != NULL) {

		for(i=0;i<GUESS_LENGTH;i++) {
			secret_code[i] = default_code[i];
		}
		secret_code[GUESS_LENGTH] = NULL_BYTE;
	}
	else {
		generate_codeword(secret_code);
	}

	/*log when client connects for the first time*/
	log_on_connect(*client_data,secret_code);

	//printf("%s\n",secret_code);


	/* play mastermind until the player runs out tries */
	while(client_data->turns_left > 0) {

		if(read(client_fd,msg,sizeof(msg)) <= 1) {
			break;
		}

		/*only grab the first 4 characters of the msg*/
		parse_guess(msg,guess);
		bzero(msg,MESSAGE_LENGTH);

		if(!is_valid(guess)) {

			if(write(client_fd,INVALID,sizeof(INVALID)) <= 1) {
				break;
			}

		}
		else {

			int correct = correct_positions(guess,secret_code);
			int incorrect = incorrect_positions(guess,secret_code);

			client_data->turns_left--;

			sprintf(msg,"[%d:%d]. You have %d turns left.",correct,
			incorrect,client_data->turns_left);

			log_guess(*client_data,guess,correct,incorrect);
			/* Send the hint */
			if(correct == CODE_LENGTH) {
				player_win = 1;
				break;
			}
			else if(write(client_fd,msg,sizeof(msg)) <= 1) {
				break;
			}

			bzero(msg,MESSAGE_LENGTH);


		}
	}

	/* Send SUCCESS message to client if it guesses the codeword
	correctly, otherwise send a FAILURE message */
	if(player_win) {
		write(client_fd,SUCCESS,sizeof(SUCCESS));

	}
	else {
		write(client_fd,FAILURE,sizeof(FAILURE));
	}

	/*log the outcome of the game */
	log_end_game(*client_data,player_win);
	close(client_fd);
	free(client_data);

	return NULL;
}



/* ---------------get current time---------------------------
 * Gets the current time 
 * Input: char *time_now
 * Output: None 
 *----------------------------------------------------------*/
void get_current_time(char *time_now) {

	time_t current = time(0);
	strftime(time_now,TIME_SIZE,"%d %m %Y %H:%M:%S",
	localtime(&current));
	
}

/* ---------------get client ip------------------------------
 * gets the client ip
 * Input: client_data_t data, char *ip4
 * Output: None 
 *----------------------------------------------------------*/
void get_client_ip(client_data_t data,char *ip4) {

	inet_ntop(AF_INET,&(data.client_addr.sin_addr),
	ip4,INET_ADDRSTRLEN);

}

/* ---------------generate codeword---------------------------
 * gets the server ip
 * Input: client_data_t data, char *ip4
 * Output: None 
 *----------------------------------------------------------*/

void get_server_ip(client_data_t data, char *ip4) {

	inet_ntop(AF_INET,&(data.server_addr.sin_addr),
	ip4,INET_ADDRSTRLEN);
}

/* ---------------log on connect--------------------------------
 * logs the essential information into the log.txt when a client
 * connects for the first time, which includes the server secret
 * that has been assigned to the client. 
 * Input: client_data_t data, char *secret_code
 * Output: None 
 *----------------------------------------------------------*/
void log_on_connect(client_data_t data, char *secret_code) {

	/* protect the critcal section */
	pthread_mutex_lock(&lock);

	/* open the log file in append mode*/
	fp = fopen(LOG_FILE, "a");

	/* buffers for time, client ip, server ip*/
	char time_now[TIME_SIZE];
	char ip4_client[INET_ADDRSTRLEN];
	char ip4_server[INET_ADDRSTRLEN];

	/* grab the time, client ip, server ip*/
	get_current_time(time_now);
	get_client_ip(data,ip4_client);
	get_server_ip(data,ip4_server);

	fprintf(fp, "[%s](%s)(%d) client connected\n",
	time_now,ip4_client,data.client_id);

	fprintf(fp, "[%s](%s) server secret = %s\n",

	time_now,ip4_server,secret_code);

	fclose(fp);

	pthread_mutex_unlock(&lock);

}

void log_guess(client_data_t data, char *guess, int correct,int incorrect) {

	/* protect the critcal section */
	pthread_mutex_lock(&lock);

	fp = fopen(LOG_FILE,"a");

	/* buffers for time, client ip, server ip*/
	char time_now[TIME_SIZE];
	char ip4_client[INET_ADDRSTRLEN];
	char ip4_server[INET_ADDRSTRLEN];

	/* grab the time, client ip, server ip*/
	get_current_time(time_now);
	get_client_ip(data,ip4_client);
	get_server_ip(data,ip4_server);

	fprintf(fp, "[%s](%s)(soc_id %d) client's guess = %s\n",
	time_now,ip4_client,data.client_id,guess);

	fprintf(fp, "[%s](%s) server's hint = [%d:%d]\n",
	time_now,ip4_server,correct,incorrect);

	fclose(fp);

	pthread_mutex_unlock(&lock);

}

void log_end_game(client_data_t data, int win)  {

	/* protect the critcal section */
	pthread_mutex_lock(&lock);

	fp = fopen(LOG_FILE,"a");

	/* buffers for time, client ip*/
	char time_now[TIME_SIZE];
	char ip4_client[INET_ADDRSTRLEN];

	/* grab the time and client ip*/
	get_current_time(time_now);
	get_client_ip(data,ip4_client);

	if(win) {
		fprintf(fp,"[%s](%s)(soc_id %d) SUCCESS game over.\n",
		time_now,ip4_client,data.client_id);
	}
	else {
		fprintf(fp,"[%s](%s)(soc_id %d) FAILURE game over.\n",
		time_now,ip4_client,data.client_id);
	}

	fclose(fp);

	pthread_mutex_unlock(&lock);

}

void parse_guess(char *msg, char *guess) {

	int i;

	for(i=0;i<GUESS_LENGTH;i++) {
		guess[i] = msg[i];
	}
	guess[CODE_LENGTH] = NULL_BYTE;
}






