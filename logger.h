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
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
#define LOG_FILE "log.txt"
#define TIME_SIZE 128
#define PATH_SIZE 100
#define NULL_BYTE '\0'
FILE *fp;



typedef struct {

	int wins;
	int clients_connected;

}stats_t;

stats_t *statistics;
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
void log_invalid_guess(int client_id,char *ip4_client, 
	pthread_mutex_t *lock);
void log_stats(pthread_mutex_t *lock);
void increment_wins();
void increment_clients();
void init_log_statistics();
/*-------------------------------------------------*/
#endif
