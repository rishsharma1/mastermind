/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
-------------------------------------------------*/

#ifndef SERVER_H
#define SERVER_H
/*------------------Libraries---------------------*/
#include <signal.h>
#include "connect.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "mastermind.h"
#include "logger.h"
#include <sys/time.h>
#include <sys/resource.h>
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define NUMBER_OF_ARGUMENTS 2
#define MAX_CLIENTS 20
#define TRUE 1
#define MAX_TURNS 10
#define MESSAGE_LENGTH 64
#define CODE_LENGTH 4

/* The rules that get sent everytime a client connects*/
static const char RULES[] = "Welcome to Mastermind.\n\n"
"I will construct a 4 letter codeword from these letters {A,B,C,D,E,F}\n"
"and it will be your job to guess my codeword.\n\n" 
"Rule 1: Your guess must be 4 characters long.\n"
"Rule 2: Your guess must contain all uppercase characters.\n"
"Rule 3: Each character in your guess must be in {A,B,C,D,E,F}.\n"
"Rule 4: You must guess within 10 trys or less.\n\n"
"Each time you make a valid guess, I will give you a hint.\n"
"The hint will be in the format of [b:m]\n\n"
"b = number of characters in your guess that are in the correct position\n"
"m = number of characters that are within the codeword but not in the\n"
"right positions in your guess.\n\n"
"Good Luck!\n\n\n\n";

/* invalid message */
static const char INVALID[] = "INVALID guess. Try Again.\0";
/* success message */
static const char SUCCESS[] = "SUCCESS\0";
/* failure message */
static const char FAILURE[] = "FAILURE\0";

/* mutal exclusion lock*/
pthread_mutex_t lock;
/* default code word */
char *default_code;

/*resource usage stats*/
struct rusage usage;
struct timeval start,end;


/* stores information about the connected client */
typedef struct {

	int client_id;
	int turns_left;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

}client_data_t;



/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
void *play_mastermind(void *data);
void parse_guess(char *msg, char *guess);
void sig_handler(int sig_flag);

/*-------------------------------------------------*/
#endif