


#include "connect.h"

int init_server_socket(int port_number, struct sockaddr_in *server_address) {

	int sockfd;


	/*Creating a TCP socket*/
	sockfd = socket(AF_NET,SOCK_STREAM,0);

	if(sockfd < 0) {
		perror("ERROR opening socket");
		exit(EXIT_FAILURE);
	}

	/*Create an address that the server will listen on (given port number) */
	bzero((char *) server_address, sizeof(*server_address));
	server_address->sin_family = AF_INET;
	server_address->sin_addr.s_addr = INADDR_ANY;
	server_address->sin_port = htons(port_number);

	/*Now we need to bind the socket to the address we created */
	if(bind(sockfd, (struct sockaddr *)server_address, sizeof(*server_address)) < 0) {
		perror("ERROR on binding");
		exit(EXIT_FAILURE);
	} 
	
	return sockfd;
}