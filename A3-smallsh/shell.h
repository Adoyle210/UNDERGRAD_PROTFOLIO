#ifndef SHELL_C
#define SHELL_C

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> //pid_t
#include <string.h>    //fork 
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

#define STACKMAX 512 //max specified in the assignment

//pid struct/functions for background stuff 
struct pidObj;
void createPidObj();
void addPid(pid_t processId);
void removePid(pid_t processId);
pid_t PopBackPid();
pid_t readPid();

//need something to pharse input 
struct inputObj;
void parseInput(char* inputBuffer,struct inputObj* Obj); 
bool is_specialChar(char *str);

//runs shell
void runShell();

//Built-in Commands
void command_exit();
int command_cd(char* InputBuffer);
void command_status();

//executing other commands 
void argList(struct inputObj* Obj,char** Args);
void Redirects(struct inputObj* Obj);
void freeInputObj(struct inputObj* Obj);
void runCommand(struct inputObj* Obj);

//signals 
void TrapStopSignal(int sig);
void TrapChildSignal(int sig);
void TrapTermSignal(int sig);

void is_bgMode();

#endif