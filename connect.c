/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/


/*------------------Libraries---------------------*/
#include "connect.h"
/*------------------------------------------------*/



/* ------------------Initialise server socket-----------------
 * Initialises the server socket, which includes building the 
 * data structures for the socket and then binding that socket
 * to the address we create.
 * Input: int port_number, sockaddr_in *server_address
 * Output: socket_fd
 *----------------------------------------------------------*/

int init_server_socket(int port_number, struct sockaddr_in *server_address) {

	int sockfd;


	/*Creating a TCP socket*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);

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
	if(bind(sockfd, (struct sockaddr *)server_address, 
		sizeof(*server_address)) < 0) {

		perror("ERROR on binding");
		exit(EXIT_FAILURE);
	} 

	return sockfd;
}


/* ------------------Initialise client socket-----------------
 * Initialises the client socket, which includes building the 
 * data structures for the socket and then connecting the socket
 * to the host server.
 * Input: char *host, int port_number
 * Output: socket_fd
 *------------------------------------------------------------*/
int init_client_socket(char *host,int port_number) {

	int sockfd;
	struct hostent *server;
	struct sockaddr_in server_address;

	/* translate the hostname into peer's IP address */
	server = gethostbyname(host);

	if(!server) {
		fprintf(stderr, "Unknown host %s\n",host);
		exit(EXIT_FAILURE);
	}

	/* build data structures for the socket */
	bzero((char *)&server_address,sizeof(server_address));
	server_address.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&server_address.sin_addr,
	server->h_length);
	server_address.sin_port = htons(port_number);

	/*creating a TCP socket*/
	sockfd = socket(AF_INET,SOCK_STREAM,0);

	if(sockfd < 0) {
		perror("Error in creating a socket to the server");
		exit(EXIT_FAILURE);
	}

	/*finally connect the socket to the host server */
	if(connect(sockfd,(struct sockaddr *)&server_address,
		sizeof(server_address)) < 0) {

		perror("Error in connecting to the host server");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	return sockfd;

}

