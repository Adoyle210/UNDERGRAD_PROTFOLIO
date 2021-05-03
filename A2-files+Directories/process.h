/****************************************************
 *  this is the header file for all the procedures 
 *  a user can do with the program 
************************************************/

#ifndef PROCESS_H
#define PROCESS_H

#define PREFIX "movies_"
#define SUFFIX ".csv"

#include <stdio.h>      //standard c library for input and output
#include <stdlib.h>
#include <string.h>     //string things 
#include <dirent.h>     //directory 
#include <sys/stat.h>   //stat
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>      //time

void largest();          //option 1
char *findLargest();            
void smallest();         //option 2
char *findSmallest();
int userChoice();        //opiion 3
int findFileName(char *);
char *makeFolderName();
void processCSV(char*, char*);


#endif 