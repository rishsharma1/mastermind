/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/

/*------------------Libraries---------------------*/
#include "client.h"
/*------------------------------------------------*/



int main(int argc,char * argv[]) {

	int sockfd, port_number;
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
		


		if(write(sockfd,msg,sizeof(msg)) < 0) {
			perror("Error: Could not write to socket.\n");
			exit(EXIT_FAILURE);
		}
		bzero(msg,MESSAGE_LENGTH);

		if(read(sockfd,msg,sizeof(msg)) < 0) {
			perror("Error: Could not read from socket.\n");
			exit(EXIT_FAILURE);
		}
		printf("Message: %s, message_size: %d, message_length: %d\n",msg,sizeof(msg),strlen(msg));

		printf("Enter your guess:");

		bzero(msg,MESSAGE_LENGTH);


	}
	return 0;
}

void get_rules(int fd) {

	char msg[RULES_LENGTH];

	read(fd,msg,sizeof(msg));
	printf("%s",msg );

}	