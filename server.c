


#include "server.h"



int main(int argc,char * argv[]) {


	struct sockaddr_in server_address, client_address;

	if(argc < NUMBER_OF_ARGUMENTS) {
		fprintf(stderr, "usage: ./server [port_number] [default_secert_code]\n");
		exit(EXIT_FAILURE);
	}



}
