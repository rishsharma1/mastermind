/*------------------Libraries---------------------*/
#ifndef MASTERMIND_H
#define MASTERMIND_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
/*-------------------------------------------------*/


/*----------------Definitions----------------------*/
static const char  colours[] = {'A','B','C','D','E','F'};
#define MAX_COLOURS 6
#define GUESS_LENGTH 4
#define NULL_BYTE '\0'

/*-------------------------------------------------*/


/*---------------Prototypes------------------------*/
int correct_positions(char *guess,char *code);
int is_valid(char *guess);
int in_array(int *array, int size, int num);
int incorrect_positions(char *guess,char *code);
void generate_codeword(char *code);
/*-------------------------------------------------*/
#endif