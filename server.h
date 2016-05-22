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
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define NUMBER_OF_ARGUMENTS 2
#define MAX_CLIENTS 20
#define TRUE 2
#define MAX_TURNS 10
#define TIME_SIZE 128
#define LOG_FILE "log.txt"

pthread_mutex_t lock;


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
/*-------------------------------------------------*/
#endif