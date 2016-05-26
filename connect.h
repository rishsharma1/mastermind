/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
-------------------------------------------------*/


/*------------------Libraries---------------------*/
#ifndef CONNECT_H
#define CONNECT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h> 
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
int init_server_socket(int port_number, 
struct sockaddr_in *server_address);
int init_client_socket(char *host,int port_number);
/*-------------------------------------------------*/
#endif


