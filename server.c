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
	int port_number, clientfd = 0, sockfd;
	default_code = NULL;


	getrusage(RUSAGE_SELF,&usage);
	start = usage.ru_utime;

	init_log_statistics();

	if (signal(SIGINT, sig_handler) == SIG_ERR) {
 		printf("\ncan't catch SIGINT\n");
 	}
 	if (signal(SIGTERM, sig_handler) == SIG_ERR) {
 		printf("\ncan't catch SIGTERM\n");
 	}

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

	/*initialise the log file*/
	init_log_file();

	/*Initialise the mutex*/
	if(pthread_mutex_init(&lock,NULL) != 0) {
		fprintf(stderr, "Mutex failed to initialise\n");
		exit(EXIT_FAILURE);
	}

	port_number = atoi(argv[1]);
	sockfd = init_server_socket(port_number,&server_address);



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
		else {
			increment_clients();
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

	close(sockfd);
	return 1;

}


/* ---------------play mastermind----------------------------
 * Plays the game mastermind with the connected client, where 
 * it will generate a random 4 letter codeword or use a 
 * default one that the client has to guess. In the process 
 * there will be some logging going onto log.txt. The client 
 * has 10 tries to guess the codeword. 
 * Input: void *data
 * Output: None 
 *----------------------------------------------------------*/
void *play_mastermind(void *data) {

	client_data_t *client_data = (client_data_t *)data;

	/*socket id for the client */
	int client_fd = client_data->client_id;
	/*buffer for the secret code */
	char secret_code[GUESS_LENGTH+1];
	/*message buffer that is going to be used to communicate*/
	char msg[MESSAGE_LENGTH],guess[CODE_LENGTH+1];
	/* client and server ip buffers*/
	char ip4_client[INET_ADDRSTRLEN];
	char ip4_server[INET_ADDRSTRLEN];
	int player_win = 0,i;

	/* get the server and client IP's*/
	inet_ntop(AF_INET,&(client_data->client_addr.sin_addr),
	ip4_client,INET_ADDRSTRLEN);

	inet_ntop(AF_INET,&(client_data->server_addr.sin_addr),
	ip4_server,INET_ADDRSTRLEN);



	/*generate a random code word or use default if provided*/
	if(default_code != NULL) {

		for(i=0;i<GUESS_LENGTH;i++) {
			secret_code[i] = default_code[i];
		}
		secret_code[GUESS_LENGTH] = NULL_BYTE;
	}
	else {
		/*generate random code word*/
		generate_codeword(secret_code);
	}

	/*log when client connects for the first time*/
	log_on_connect(client_fd,ip4_client,
	ip4_server,secret_code,&lock);


	/* play mastermind until the player runs out tries */
	while(client_data->turns_left > 0) {

		if(read(client_fd,msg,sizeof(msg)) <= 1) {
			break;
		}

		/*only grab the first 4 characters of the msg*/
		parse_guess(msg,guess);
		bzero(msg,MESSAGE_LENGTH);

		/*check if the guess is valid*/
		if(!is_valid(guess)) {

			client_data->turns_left--;
			log_invalid_guess(client_fd,ip4_client,&lock);

			if(write(client_fd,INVALID,sizeof(INVALID)) <= 1) {
				break;
			}


		}
		else {

			/*number of correct and incorrect for current guess*/
			int correct = correct_positions(guess,secret_code);
			int incorrect = incorrect_positions(guess,secret_code);

			client_data->turns_left--;

			sprintf(msg,"[%d:%d]. You have %d turns left.",correct,
			incorrect,client_data->turns_left);

			/*log the guess */
			log_guess(client_fd,guess,correct,
			incorrect,ip4_client,ip4_server,&lock);
			
			/* Send the hint */
			if(correct == CODE_LENGTH) {
				player_win = 1;
				increment_wins();
				break;
			}
			else if(client_data->turns_left == 0) {
				break;
			}
			else if(write(client_fd,msg,sizeof(msg)) <= 1) {
				break;
			}

			bzero(msg,MESSAGE_LENGTH);


		}
	}

	bzero(msg,MESSAGE_LENGTH);
	/* Send SUCCESS message to client if it guesses the codeword
	correctly, otherwise send a FAILURE message */
	if(player_win) {
		write(client_fd,SUCCESS,sizeof(SUCCESS));

	}
	else {
		sprintf(msg,"The secret code was %s",
		secret_code);
		write(client_fd,FAILURE,sizeof(FAILURE));
		write(client_fd,msg,sizeof(msg));
	}

	/*log the outcome of the game */
	log_end_game(client_fd,ip4_client,
	player_win, &lock);

	close(client_fd);
	free(client_data);

	return NULL;
}


/* ---------------parse guess---------------------------------
 * Only take the first 4 characters of the msg recieved from 
 * the client.
 * Input: char *msg, char *guess
 * Output: None 
 *----------------------------------------------------------*/
void parse_guess(char *msg, char *guess) {

	int i;

	for(i=0;i<GUESS_LENGTH;i++) {
		guess[i] = msg[i];
	}
	guess[CODE_LENGTH] = NULL_BYTE;
}

void sig_handler(int sig_flag) {

	if(sig_flag == SIGINT || sig_flag == SIGTERM) {

		getrusage(RUSAGE_SELF,&usage);
		end = usage.ru_utime;

		printf("Started at: %ld.%lds\n",start.tv_sec,start.tv_usec);
		printf("Ended at: %ld.%lds\n",end.tv_sec,end.tv_usec);
		printf("Shared memory: %ld\n",usage.ru_ixrss );
		printf("%ld\n",usage.ru_maxrss);

		log_stats(&lock);
		exit(EXIT_SUCCESS);
	}
}






