#ifndef PROCESSOR_C
#define PROCESSOR_C

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> // for threads
#include <unistd.h>
#include <string.h>

struct buffer{
    int  count;  
    int  index;
    int  numchar;   //max is 10000
    char file[50000];         
};

struct passTwo{
  struct buffer* producer;
  struct buffer* consumer;
};

int check_status(char file[]);

void *readLines(void* args); // reads lines of standard input 
void *lineSeparator(void* args); //line separators are replaced by a space
void *plusSign(void* args); //plus signs are replaced by the ^ 
void *output(void* args); //process data to standard output as lines of exactly 80 characters 

#endif