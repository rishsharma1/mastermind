/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/

/*------------------Libraries---------------------*/
#include "server.h"
/*------------------------------------------------*/




int main(int argc,char * argv[]) {


	struct sockaddr_in server_address, client_address;
	int port_number, client_len, sockfd;

	if(argc < NUMBER_OF_ARGUMENTS) {
		fprintf(stderr, "usage: ./server port_number [default_secert_code]\n");
		exit(EXIT_FAILURE);
	}

	port_number = atoi(argv[1]);





}
