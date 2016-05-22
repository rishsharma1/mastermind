/*------------------Libraries---------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
const char  colours[] = {'A','B','C','D','E','F'};
#define MAX_COLOURS 6
#define GUESS_LENGTH 4

/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
int correct_positions(char *guess,char *code);
int is_valid(char *guess);
/*-------------------------------------------------*/
