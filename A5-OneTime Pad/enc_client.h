#ifndef ENC_CLIENT_H
#define ENC_CLIENT_H
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
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netdb.h> 
#include <fcntl.h>
#include <ctype.h>
#include <assert.h>

#define LENGTH 512
#define BUFFER_SIZE 100000

//Functions
void getMSG(char* buffer, FILE* fp); 
void sendMSG(char* buffer, int socketFD);
void MustFree(char* mustFree);


#endif