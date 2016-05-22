/*------------------Details------------------------
  Name: Rishabh Sharma
  Student Number: 694739
 -------------------------------------------------*/



/*------------------Libraries---------------------*/
 #include "mastermind.h"
/*------------------------------------------------*/




int main(int argc, char *argv[]) {

	char guess[] = "FFFF";


	if(is_valid(guess)) {
		printf("%s is a valid guess\n",guess);
	}
	else {
		printf("%s is a invalid guess\n",guess);
	}
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