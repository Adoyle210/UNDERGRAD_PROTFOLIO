/********************************************************
 * this is the header file for the movie functions 
 * this is also there the movie struct is defined
*********************************************************/
#ifndef Movie_H     //header guards for the h file 
#define Movie_H 

struct list;        //array of movies as a link list 
int in_range();     //checks if use imput is in range 
struct list* setup_movie(int );
void load_movie(struct list* movie_data , int num_movies, FILE * file);
int choice_check();         //checks and returns a proper int
void year(struct list* , int);   //option one 
void rating(struct list* , int); //option two 
void lang(struct list* , int);   //option three 

#endif