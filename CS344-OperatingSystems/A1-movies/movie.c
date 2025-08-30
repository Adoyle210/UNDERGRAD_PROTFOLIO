/********************************************************
 * this is where the movie functions to run the program 
 * are at  
*********************************************************/
#include <stdio.h> //standard c library for input and output
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include "movie.h"

// this is the movie struct and it stores each movies data 

struct movie{
  char title[50];
  int year;
  char languages[100];
  double rating; 
  struct movie* next;
};

struct list{
    struct movie* head;
};

/********************************************************
  This sets up the struct to be loaded 
*********************************************************/
struct list* setup_movie(int num_movies){
  struct list* list = malloc(sizeof(num_movies));
  list->head = NULL;
  return list;
}
/********************************************************
  this loads up the struct that has been set up 
*********************************************************/
void load_movie(struct list *movie_data, int num_movies, FILE *file){
  
  char holder;
  int line = 0;
  while((holder=fgetc(file)) != EOF) {
    if(holder == '\n'){
      line++;
    }
    if(line == 1){ 
      break;      //break at line two to start loading 
    }
  }
  for(int i = 1; i < num_movies; i++){
    assert(movie_data);
    struct movie* movie = malloc(sizeof(struct movie));
    char ch;
    int data = 0;
    char rate[4];
    char *ptr;
    char yr[5];
    int c = 0;
    while ((ch = fgetc(file)) != '\n'){
      if(ch == ','){
        data += 1;
        c = 0;
      }
      else if(ch!= ',' && data == 0){ //title
        movie->title[c] = ch;
        c += 1;
      }
      else if(ch!= ',' && data == 1){ //year
        yr[c] = ch;
        c += 1;
        if(c == 4){
          movie->year = atoi(yr);   //conveting string year to an in 
        }
      }
      else if(ch != ',' && ch != '[' && ch != ']' && data == 2){ //languages
        movie->languages[c] = ch;
        c += 1;
      }
      else if(ch != ',' && data == 3){ //rating
        rate[c] = ch;
        c += 1;
        if(c == 3){
          movie->rating = strtod(rate, &ptr);
        }
      }
    }
    movie->next = movie_data->head;
    movie_data->head = movie;
  }
}

/********************************************************
  this checks the choice and returns a proper choice 
*********************************************************/
int choice_check(){
  int choice = 0;
  do{
    scanf("%d", &choice);
    if(choice > 4 || choice < 0){
      printf("\nYou entered an incorrect choice. Try again.\n");
      printf("1. Show movies released in the specified year \n 2. Show highest rated movie for each year \n 3. Show the title and year of release of all movies in a specific language \n 4. Exit from the program\n");
      printf("Enter a choice from 1 to 4: ");
    }
  }while(choice > 4 || choice < 0);
  return choice;
}


/********************************************************
  this is for the year choice in main 
*********************************************************/ 
void year(struct list* movie_list, int num_movies){ // option one
    int yr = 0; 
    int found = 0;
    printf("Enter the year for which you want to see movies: ");
    scanf("%d", &yr);  //get year from user 
    struct movie* curr = movie_list->head;
    while(curr != NULL){ // loop through and print names
      if(curr->year == yr){
        printf("%s \n", curr->title);
        found = 1;
      }
      curr = curr->next;
      
    }
    if(found == 0){ // if no movies from that year then print no movies
      printf("\n No data about movies released in the year %d \n", yr);
    }
}

/********************************************************
  this is for qsort to compare the years and ratings 
  but when using q sort u get a seg fault because the movie 
  struct is in the list one so it does not work 
*********************************************************/ 
int comparator(const void * a, const void* b){
  if(((struct movie*)a)->year == ((struct movie*)b)->year){            
    return ((struct movie*)a)->rating < ((struct movie*)b)->rating;else
  }
  return ((struct movie*)a)->year < ((struct movie*)b)->year;
}	 

/********************************************************
  this is for the rating choice in main 
*********************************************************/ 
void rating(struct list* movie_list, int num_movies){ //option two 
   //qsort(movie_list, num_movies, sizeof(movie_list), comparator);
    struct movie* curr = movie_list->head;
    int curr_year = -1;
    for(int i = 0; i < num_movies - 1; i++){
        if(curr->year != curr_year){
            printf("%d %.1f %s\n", curr->year, curr->rating, curr->title);
        }
        curr_year = curr->year;
        curr = curr->next;
    }
    printf("\n");
}

/********************************************************
  this is for the lang choice in main 
*********************************************************/ 
void lang(struct list* movie_list, int num_movies){   //option three 
  char lang[20];
  int found = 0;
  struct movie* curr = movie_list->head;
  printf("Enter the language for which you want to see movies: ");
  scanf("%s", lang);
  for(int i = 0; i < num_movies - 1; i++){ //looping all the movies
    int j = 0; //loop through movie list 
    int c = 0; //loop through user lang choice 
    int l = strlen(lang); //length of user lang choice
    int n = strlen(curr->languages);
    int consec = 0;
    
    while(j != n){ //looping list of langs
      if(curr->languages[j] == lang[c]){
        consec++;
      }
      else if(curr->languages[j] == ';'){ //reset lang 
        consec = 0;
        c = -1;
      }
      else{
        consec = 0;
      }
      
      if(consec == l){
        found++;
        if(found > 1){
          printf("\n ");
        }
        printf("%d %s", curr->year, curr->title);
        break;
      }

      j++;
      c++;
    }
    curr = curr->next;
    
  }
  if(found == 0){
      printf("No data about movies released in %s\n", lang);
  }
  else{
    printf("\n");
  }
} 