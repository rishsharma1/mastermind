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

	if(argc < NUMBER_OF_ARGUMENTS) {
		fprintf(stderr, "Usage: ./client host_name/IP_address port_number\n");
		exit(EXIT_FAILURE);
	}

	host = argv[1];
	port_number = atoi(argv[2]);

	sockfd = init_client_socket(host,port_number);	

}