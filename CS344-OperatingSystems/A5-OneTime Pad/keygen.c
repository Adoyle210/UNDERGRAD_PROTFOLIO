#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


/******************************************************************************************
 *  if there are 2 arguments, we do the following things:
 * 		program creates a key file of specified length
 * 		creates a file of characters keyLength long with standard Unix randomization methods
 * 		allowed characters are 26 characters of the alphabet and the space character
 * 		does not add spaces between characters like normally done
 ********************************************************************************************/
int main(int argc, char *argv[]){
	srandom(time(NULL));	//this is the seed for ran numbers 
	char *randomized_String;
	if (argc != 2)	{ //checking for 2 args 
		printf("not enough arguments were specified\n");
		exit(1);
	}
	if (argc == 2){
		int string_Length;
		string_Length = atoi(argv[1]); //converting string into numbers 
		randomized_String = (char*)malloc(sizeof(char)*(string_Length+1));
        static const char available_Characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
        int i;
        for (i = 0; i < string_Length; i++) {
			// For each element in the string array put a random character using one of the available characters
	    	randomized_String[i] = available_Characters[rand() % (sizeof(available_Characters) - 1)];
		}
		randomized_String[string_Length] = 0; // this make the last element null terminated
		printf("%s\n", randomized_String);
	}
	// Free the allocated string memory
	free(randomized_String);
	return 0;
}
