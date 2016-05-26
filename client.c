/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/

/*------------------Libraries---------------------*/
#include "client.h"
/*------------------------------------------------*/





int main(int argc,char * argv[]) {

	int port_number;
	char *host;
	char msg[MESSAGE_LENGTH];


	if(argc < NUMBER_OF_ARGUMENTS) {
		fprintf(stderr, "Usage: ./client host_name/IP_address port_number\n");
		exit(EXIT_FAILURE);
	}

	host = argv[1];
	port_number = atoi(argv[2]);


	sockfd = init_client_socket(host,port_number);
	/*get the rules from the server*/
	get_rules(sockfd);
	printf("Enter your guess:");

	while(fgets(msg,sizeof(msg),stdin)) {
		


		if(write(sockfd,msg,sizeof(msg)) <= 1) {
			perror("Error: Could not write to socket.\n");
			break;
		}
		bzero(msg,MESSAGE_LENGTH);

		if(read(sockfd,msg,sizeof(msg)) <= 1) {
			perror("Error: Could not read from socket.\n");
			break;
		}
		printf("%s\n",msg);

		/* end the client if we get a SUCCESS or FAILURE message from the server*/
		if(strcmp(msg,SUCCESS) == 0) {
			break;
		}
		else if(strcmp(msg,FAILURE) == 0) {
			
			bzero(msg,MESSAGE_LENGTH);
			/* find what the code word was was it*/
			if(read(sockfd,msg,sizeof(msg)) <= 1) {
				perror("Error: Could not read from socket.\n");
			}
			printf("%s\n",msg);
			break;	
		}
		printf("Enter your guess:");

		bzero(msg,MESSAGE_LENGTH);


	}
	close(sockfd);
	
	return 0;
}


void get_rules(int fd) {

	char msg[RULES_LENGTH];

	read(fd,msg,sizeof(msg));
	printf("%s",msg );

}