/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/

/*------------------Libraries---------------------*/
#include "client.h"
/*------------------------------------------------*/



int main(int argc,char * argv[]) {

	int sockfd = 0, port_number,n,bufflen,datalen;
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

	while(fgets(msg,sizeof(msg),stdin)) {
		

		datalen = strlen(msg);
		int tmp = htonl(datalen);

		if(write(sockfd,(char*)&tmp,sizeof(tmp)) < 0) {
			perror("Error: Could not write to socket.\n");
			exit(EXIT_FAILURE);
		}

		if(write(sockfd,msg,datalen) < 0) {
			perror("Error: Could not write to socket.\n");
			exit(EXIT_FAILURE);
		}

		bzero(msg,MESSAGE_LENGTH);


		if(read(sockfd,(char*)&bufflen,sizeof(bufflen)) < 0) {
			perror("Error: Could not read from socket.");
			break;
		}

		bufflen = ntohl(bufflen);

		if(read(sockfd,msg,bufflen) < 0) {
			perror("Error: Could not read from socket.");
			break;
		}
		sleep(1);

		printf("%s\n",msg);
		bzero(msg,MESSAGE_LENGTH);


	}
	return 0;
}

void get_rules(int fd) {

	char msg[RULES_LENGTH];

	read(fd,msg,sizeof(msg));
	printf("%s",msg );

}	