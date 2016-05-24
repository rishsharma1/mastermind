/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
-------------------------------------------------*/

/*------------------Libraries---------------------*/
#ifndef SERVER_H
#define SERVER_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <assert.h>
#include "connect.h"
#include "mastermind.h"
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define NUMBER_OF_ARGUMENTS 2
#define MAX_CLIENTS 20
#define TRUE 1
#define MAX_TURNS 10
#define TIME_SIZE 128
#define LOG_FILE "log.txt"
#define MESSAGE_LENGTH 64
#define CODE_LENGTH 4

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

static const char INVALID[] = "INVALID guess. Try Again.\0";
static const char SUCCESS[] = "SUCCESS\0";
static const char FAILURE[] = "FAILURE\0";
 
pthread_mutex_t lock;
char *default_code;


typedef struct {

	int client_id;
	int turns_left;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;

}client_data_t;
/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
void log_on_connect(client_data_t data,FILE *fp);
void get_current_time(char *time_now);
void get_client_ip(client_data_t data,char *ip4);
void *play_mastermind(void *data);
void parse_guess(char *msg, char *guess);
/*-------------------------------------------------*/
#endif