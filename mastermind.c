/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/



/*------------------Libraries---------------------*/
 #include "mastermind.h"
/*------------------------------------------------*/


/* ------------------Check for validity------------------------
 * Checks whether the guess made by the client is a valid guess.
 * If a input guess contains all uppercase letters that are 
 * within the 6 colour span {A,B,C,D,E,F} then it is a valid guess,
 * otherwise if any of the above constraints are violated  it is 
 * a invalid guess.
 * Input: char *guess
 * Output: 1 for valid guess, 0 for invalid guess 
 *----------------------------------------------------------*/
int is_valid(char *guess) {

	int i,j;
	if(strlen(guess) != GUESS_LENGTH) {
		return 0;
	}

	for(i=0;i<GUESS_LENGTH;i++) {

		int valid_flag = 0;

		if(!isupper(guess[i])) {
			return 0;
		}

		for(j=0;j<MAX_COLOURS;j++) {

			if(guess[i] == colours[j]) {
				valid_flag = 1;
				break;
			}
		}

		if(!valid_flag) {
			return 0;
		}
	}

	return 1;
}

/* ---------------Check for correct positions-----------------
 * Checks the guess, looking for characters in the 
 * guess that are in the correct positions with respect to the 
 * secret code.
 * Input: char *guess, char *code
 * Output: number of characters in the correct position
 *----------------------------------------------------------*/
int correct_positions(char *guess,char *code) {

	int correct_pos = 0,i;

	for(i=0;i<GUESS_LENGTH;i++) {

		if(guess[i] == code[i]) {
			correct_pos++;
		}

	}
	return correct_pos;
}

/* ---------------in array------------------------------------
 * Checks if the number is in the array 
 * Input: int *array, int size, int number
 * Output: 1 if number is in array, 0 otherwise 
 *----------------------------------------------------------*/
int in_array(int *array, int size, int num) {
	
	int i;

	for(i=0;i<size;i++) {
		if(array[i] == num) {
			return 1;
		}
	}
	return 0;
} 

/* ---------------Check for incorrect positions---------------
 * Checks the guess, looking for characters in the guess that 
 * are in the secret code but not in the right position
 * Input: char *guess, char *code
 * Output: number of characters that are in the incorrect positions 
 *----------------------------------------------------------*/
int incorrect_positions(char *guess,char *code) {

	int incorrect_pos = 0,i,j;
	int correct_index[GUESS_LENGTH];
	int correct = 0;

	/* keeps track of the correct positions */
	for(i=0;i<GUESS_LENGTH;i++) {

		if(guess[i] == code[i]) {
			correct_index[correct++] = i;
		}
	}

	for(i=0;i<GUESS_LENGTH;i++) {

		if(guess[i] != code[i]) {

			for(j=0;j<GUESS_LENGTH;j++) {

				if(guess[i] == code[j] && 
				!in_array(correct_index,correct,j)) {
					incorrect_pos++;
					correct_index[correct++] = j;
				}
			}
		}
	}

	return incorrect_pos;
}


/* ---------------generate codeword---------------------------
 * Generates a random codeword that is within the constraints 
 * Input: char *code
 * Output: None 
 *----------------------------------------------------------*/
void generate_codeword(char *code) {

	srand(time(NULL));
	int num = 0;

	while(num < GUESS_LENGTH) {

		int index = rand() % MAX_COLOURS;
		code[num++] = colours[index];
	}
	code[num] = NULL_BYTE;
}



