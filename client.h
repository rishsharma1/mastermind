/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
-------------------------------------------------*/

/*------------------Libraries---------------------*/
#ifndef CLIENT_H
#define CLIENT_H
#include "connect.h"
#include <signal.h>
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define NUMBER_OF_ARGUMENTS 3
#define TRUE 1
#define RULES_LENGTH 700
#define MESSAGE_LENGTH 64
#define NULL_BYTE '\0'

static const char SUCCESS[] = "SUCCESS\0";
static const char FAILURE[] = "FAILURE\0";

int sockfd;
/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
void get_rules(int fd);
void sig_handler(int sig);
/*-------------------------------------------------*/
#endif



