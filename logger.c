/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/

/*------------------Libraries---------------------*/
#include "logger.h"
/*------------------------------------------------*/


/* ---------------initialise the log file---------------------
 * Initialise the log file that is going to store information 
 * regarding multiple clients interactions with the server
 * when playing the game mastermind.
 *----------------------------------------------------------*/
void init_log_file() {

	/* new log file */
	fp = fopen(LOG_FILE,"w");

	if(!fp) {
		fprintf(stderr, "Error: Log file failed to create\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
}


/* ---------------log on connect--------------------------------
 * Logs the guess each time client guesses, including the hint 
 * that is given by the server to the client. 
 *----------------------------------------------------------*/
void log_guess(int client_id, char *guess, int correct,int incorrect,
	char *ip4_client, char *ip4_server, pthread_mutex_t *lock) {

	/* protect the critcal section */
	pthread_mutex_lock(lock);

	fp = fopen(LOG_FILE,"a");

	/*buffer for time*/
	char time_now[TIME_SIZE];

	/* grab the time*/
	get_current_time(time_now);

	fprintf(fp, "[%s](%s)(soc_id %d) client's guess = %s\n",
	time_now,ip4_client,client_id,guess);

	fprintf(fp, "[%s](%s) server's hint = [%d:%d]\n",
	time_now,ip4_server,correct,incorrect);

	fclose(fp);

	pthread_mutex_unlock(lock);

}


/* ---------------log end game---------------------------------
 * Logs the outcome of the game, which can either result in the
 * player wining the game or failing (running out of turns).
 *----------------------------------------------------------*/
void log_end_game(int client_id,char *ip4_client, int win,
	pthread_mutex_t *lock)  {

	/* protect the critcal section */
	pthread_mutex_lock(lock);

	fp = fopen(LOG_FILE,"a");

	/* buffers for time, client ip*/
	char time_now[TIME_SIZE];

	/* grab the time*/
	get_current_time(time_now);

	if(win) {
		fprintf(fp,"[%s](%s)(soc_id %d) SUCCESS game over.\n",
		time_now,ip4_client,client_id);
	}
	else {
		fprintf(fp,"[%s](%s)(soc_id %d) FAILURE game over.\n",
		time_now,ip4_client,
		client_id);
	}

	fclose(fp);

	pthread_mutex_unlock(lock);

}


/* ---------------log on connect--------------------------------
 * logs the essential information into the log.txt when a client
 * connects for the first time, which includes the server secret
 * that has been assigned to the client. 
 *----------------------------------------------------------*/
void log_on_connect(int client_id,char *ip4_client,char *ip4_server, 
	char *secret_code, pthread_mutex_t *lock) {

	/* protect the critcal section */
	pthread_mutex_lock(lock);

	/* open the log file in append mode*/
	fp = fopen(LOG_FILE, "a");

	/* buffer for time*/
	char time_now[TIME_SIZE];


	/* grab the time*/
	get_current_time(time_now);


	fprintf(fp, "[%s](%s)(%d) client connected\n",
	time_now,ip4_client,client_id);

	fprintf(fp, "[%s](%s) server secret = %s\n",
	time_now,ip4_server,secret_code);

	fclose(fp);

	pthread_mutex_unlock(lock);

}

/* ---------------get current time---------------------------
 * Gets the current time 
 * Input: char *time_now
 * Output: None 
 *----------------------------------------------------------*/
void get_current_time(char *time_now) {

	time_t current = time(0);
	strftime(time_now,TIME_SIZE,"%d %m %Y %H:%M:%S",
	localtime(&current));
	
}

