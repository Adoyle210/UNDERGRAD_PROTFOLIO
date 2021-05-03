/********************************************************
 * this is where the main function is located and it runs 
 * the whole program 
*********************************************************/
#include <stdio.h> //standard c library for input and output
#include <stdlib.h>
#include "movie.h"

int main(int argc, const char *argv[]){
    //checking for file using argc 
    if(argc != 2){
        printf("Error: must enter one files in the command line to load in the movie data\n");
        exit(1);
    }
    const char *movie_file = argv[1];
    char c;
    FILE *file = fopen(movie_file, "r"); //opens to allow reading
    int num_movies = 0;                 // stores  num of movies
    for (c = getc(file); c != EOF; c = getc(file)){
        if (c == '\n'){           // Increment count if this character is newline
            num_movies += 1; 
        }
    }
    if (file == NULL){
		  printf("open failed on \"%s\"\n", movie_file);
		  perror("in main");
		  exit(1);
	  }
    fclose(file);
    file = fopen(movie_file, "r"); //opens to allow reading
    struct list *movie_data = setup_movie(num_movies);  // setup struct for data 
    load_movie(movie_data, num_movies, file);
    printf("Processed file \"%s\" and parsed data for %d movies\n", movie_file, num_movies); // print statement 
    int choice = 0;
    // gives different options till exits with 4 
    do{
        // print a list of options 
        printf(" 1. Show movies released in the specified year \n 2. Show highest rated movie for each year \n 3. Show the title and year of release of all movies in a specific language \n 4. Exit from the program\n");
        // ask user for there choice 
        printf("Enter a choice from 1 to 4: ");
        //check the users choice and error handle if needed
        choice = choice_check();
        //call choice function bases on user input 
        if(choice == 1){year(movie_data, num_movies);}
        else if (choice == 2){rating(movie_data, num_movies);}
        else if (choice == 3){lang(movie_data, num_movies); }

    }while(choice != 4);

    fclose(file);
    return 0;
}