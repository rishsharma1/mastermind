/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
-------------------------------------------------*/

/*------------------Libraries---------------------*/
#ifndef CLIENT_H
#define CLIENT_H
#include "connect.h"
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define NUMBER_OF_ARGUMENTS 3
#define TRUE 1
#define RULES_LENGTH 700
#define MESSAGE_LENGTH 64
#define NULL_BYTE '\0'

static const char SUCCESS[] = "SUCCESS\0";
static const char FAILURE[] = "FAILURE\0";
/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
void get_rules(int fd);
/*-------------------------------------------------*/
#endif



