#include "shell.h"

/*****************************************************************
 * this is the main that runs the whole program 
******************************************************************/
int main(int argc, char **argv){
    createPidObj();
    runShell(); // singleton for shell.
    return 0;
}