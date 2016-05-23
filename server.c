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
	FILE *fp;
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


		/*log when client connects for the first time*/
		log_on_connect(*client_data,fp);
		/*send rules to client*/
		write(clientfd,rules,sizeof(rules));	


		/* Create this new thread*/
		/*pthread_t thread_id;
		if(pthread_create(&thread_id, NULL,test,(void *)3)) {
			fprintf(stderr, "Failed to create thread.\n");
			exit(EXIT_FAILURE);
		}
		*/
		/* Detach this thread */
		/*if(pthread_detach(thread_id)) {
			fprintf(stderr, "Failed to detach thead.\n");
			exit(EXIT_FAILURE);
		}
		*/


	}

	close(server_address);
	return 1;

}

void *play_mastermind(void *data) {

	client_data_t *client_data = (client_data_t *)data;

	int client_fd = client_data->client_id;
	char secret_code[GUESS_LENGTH+1];

	/*generate a random code word or use default if provided*/
	if(default_code != NULL) {

		for(int i=0;i<GUESS_LENGTH;i++) {
			secret_code[i] = default_code[i];
		}
		secret_code[GUESS_LENGTH] = NULL_BYTE;
	}
	else {
		generate_codeword(secret_code);
	}

	/* play mastermind until the player runs out tries */
	while(client_data->turns_left > 0) {

	}


}




void get_current_time(char *time_now) {

	time_t current = time(0);
	strftime(time_now,TIME_SIZE,"%d %m %Y %H:%M:%S",localtime(&current));
	
}

void get_client_ip(client_data_t data,char *ip4) {

	inet_ntop(AF_INET,&(data.client_addr.sin_addr),ip4,INET_ADDRSTRLEN);

}

void log_on_connect(client_data_t data,FILE *fp) {


	/* open the log file in append mode*/
	fp = fopen(LOG_FILE, "a");
	char time_now[TIME_SIZE];
	char ip4[INET_ADDRSTRLEN];

	get_current_time(time_now);
	get_client_ip(data,ip4);

	fprintf(fp, "[%s](%s)(%d) client connected\n",time_now,ip4,data.client_id);
	fclose(fp);
}






