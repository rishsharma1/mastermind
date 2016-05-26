/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
-------------------------------------------------*/

#ifndef LOGGER_H
#define LOGGER_H
/*------------------Libraries---------------------*/
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define LOG_FILE "log.txt"
#define TIME_SIZE 128
FILE *fp;
/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
void init_log_file();
void log_guess(int client_id, char *guess, int correct,int incorrect,
char *ip4_client, char *ip4_server, pthread_mutex_t *lock);
void log_end_game(int client_id,char *ip4_client, int win,
pthread_mutex_t *lock); 
void log_on_connect(int client_id,char *ip4_client,char *ip4_server, 
char *secret_code, pthread_mutex_t *lock);
void get_current_time(char *time_now);
/*-------------------------------------------------*/
#endif
