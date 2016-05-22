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

	if(argc < NUMBER_OF_ARGUMENTS) {
		fprintf(stderr, "Usage: ./server port_number [default_secert_code]\n");
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
			char ip4[INET_ADDRSTRLEN];
			inet_ntop(AF_INET,&(client_address.sin_addr),ip4,INET_ADDRSTRLEN);
			printf("connection accepted from client %s\n",ip4);
		}
	}

	close(server_address);
	return 1;

}
