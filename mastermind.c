/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/



/*------------------Libraries---------------------*/
 #include "mastermind.h"
/*------------------------------------------------*/




int main(int argc, char *argv[]) {

	char guess[] = "FFFF";
	char code[] = "FBEA";


	printf("code: %s, guess: %s\n",code,guess);

	if(is_valid(guess)) {
		printf("%s is a valid guess\n",guess);
	}
	else {
		printf("%s is a invalid guess\n",guess);
	}
	printf("guess: %s has %d correct positions\n",guess,correct_positions(guess,code));
	printf("guess: %s has %d incorrect positions\n",guess,incorrect_positions(guess,code));


}

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

	for(int i=0;i<GUESS_LENGTH;i++) {

		int valid_flag = 0;

		if(!isupper(guess[i])) {
			return 0;
		}

		for(int j=0;j<MAX_COLOURS;j++) {

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

	int correct_pos = 0;

	for(int i=0;i<GUESS_LENGTH;i++) {

		if(guess[i] == code[i]) {
			correct_pos++;
		}

	}
	return correct_pos;
}

int in_array(int *array, int size, int num) {

	for(int i=0;i<size;i++) {
		if(array[i] == num) {
			return 1;
		}
	}
	return 0;
} 

int incorrect_positions(char *guess,char *code) {

	int incorrect_pos = 0;
	int correct_index[GUESS_LENGTH];
	int correct = 0;

	/* keeps track of the correct positions */
	for(int i=0;i<GUESS_LENGTH;i++) {

		if(guess[i] == code[i]) {
			correct_index[correct++] = i;
		}
	}


	for(int i=0;i<GUESS_LENGTH;i++) {

		if(guess[i] != code[i]) {

			for(int j=0;j<GUESS_LENGTH;j++) {

				if(guess[i] == code[j] && !in_array(correct_index,correct,j)) {
					incorrect_pos++;
					break;
				}
			}
		}
	}

	return incorrect_pos;
}



