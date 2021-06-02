#ifndef ENC_SERVER_H
#define ENC_SERVER_H
#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>

#define LISTEN_QUEUE 5
#define LENGTH 512
#define NUMBER_ALLOWED_CHARS 27
#define BUFFER_SIZE 1000000

//globals: 
char validChars[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
pid_t children[LISTEN_QUEUE] = {0};
int NumChildren = 0;

//functions 
int findNewLine(char* buffer, int start); 
int getCharIndex(char c);
char* getFromBuffer(char* buffer, int start, int end); 
int getNumChars(char* buffer);
char getType(char* buffer);
void parseBuffer(char* buffer, char** msgs); 
void addToBuffer(char* buffer, char* read);
int moveDown(char* str, int len, int index, int shifts);
void encrypt(char* buffer, int newsockfd);
void wait_for_child(int sig);

#endif