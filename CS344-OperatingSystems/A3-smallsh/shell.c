#include "shell.h"

//the following are all the pid struct/functions for background stuff 
/*****************************************************************
 * this is a struct for pid (processes id's)
******************************************************************/
struct pidObj{
    int pid_val;
    pid_t backgroundPids[STACKMAX];
};

struct pidObj pidStack; //Global
/*****************************************************************
 * this is loads the pid struct with the in -1 
******************************************************************/
void createPidObj(){
    int i;
    pidStack.pid_val = -1;
    for(i = 0; i < STACKMAX; i++){
        pidStack.backgroundPids[i] = -1;
    }
}

/*****************************************************************
 * this adds/pushes back a pid to the stack
******************************************************************/
void addPid(pid_t processId){
    pidStack.backgroundPids[++(pidStack.pid_val)] = processId;
}

/*****************************************************************
 * this removes a pid if an ealier background job (bg) is done 
******************************************************************/
void removePid(pid_t processId){
    int i;
    int pidPos;
    for(i = 0; i < pidStack.pid_val+ 1;i++){
        if(pidStack.backgroundPids[i] == processId){
            pidPos = i;
            break;
        }
    }
    for(i = pidPos; i < pidStack.pid_val + 1;i++){
        pidStack.backgroundPids[i] = pidStack.backgroundPids[i+1];
    }
    pidStack.pid_val--;
}

/*****************************************************************
 * this removes a pid from top of stack
******************************************************************/
pid_t PopBackPid(){
    return pidStack.backgroundPids[pidStack.pid_val--];
}

/*****************************************************************
 * this reads a pid from top of the stack
******************************************************************/
pid_t readPid(){
    return pidStack.backgroundPids[pidStack.pid_val];
}

/*****************************************************************
 * this is a struct that stores all the different elements in 
 *  the command (values loaded when command is parsed)
******************************************************************/
struct inputObj{
    bool Background;
    char InputFile[128];
    char OutputFile[128];
    char Command[1028];
    int NumArgs;
    char *Arguments[512];
};

//global
int lastForegroundStatus;
//NUMBER ONE COMMAND PROMTS
/*****************************************************************
 * this function is to run the shell and loops untill status says
 * otherwise
*****************************************************************/
void runShell(){
    char inputBuffer[1028];
    struct inputObj *Obj;
    int ForegroundStatus;   
    //init signals
    struct sigaction StopSignal;
    StopSignal.sa_handler = TrapStopSignal;
    StopSignal.sa_flags = 0;

    struct sigaction TermSignal;
    TermSignal.sa_handler = TrapTermSignal;
    StopSignal.sa_flags = 0;

    struct sigaction ChildSignal;
    ChildSignal.sa_handler = TrapChildSignal;
    StopSignal.sa_flags = 0;
    do{
        //reseting signal handlers:
        sigaction(SIGTSTP,&StopSignal, NULL);
        sigaction(SIGINT,&TermSignal, NULL);
        sigaction(SIGCHLD,&ChildSignal, NULL);
    
        is_bgMode();

        //clearing stdin and out:
        fflush(stdout);
        fflush(stdin);

        printf(": ");
        memset(inputBuffer,'\0',sizeof(inputBuffer));
        fgets(inputBuffer,sizeof(inputBuffer),stdin); //getting command line
        
        fflush(stdout);
        fflush(stdin);

        if(strncmp(inputBuffer,"exit",4) == 0){ // exit shell.
            command_exit();
            exit(0);
        }
        else if(strncmp(inputBuffer, "#",1) == 0){ //comments
            continue;
        }
        else if(strncmp(inputBuffer,"cd", 2) == 0){ // hange directory
            command_cd(inputBuffer);  //change to command cd 
        }
        else if(strncmp(inputBuffer,"status",6) == 0){ //checking last fg command status
            if(WEXITSTATUS(lastForegroundStatus)){
                ForegroundStatus = WEXITSTATUS(lastForegroundStatus); //check if extied
            }
            else{
                ForegroundStatus = WTERMSIG(lastForegroundStatus); //check if terminated by signal
            }
            printf("exit value %d\n",ForegroundStatus);
        }
        else{
            if(inputBuffer != NULL && strcmp(inputBuffer,"") != 0){
                //read in a command
                Obj = malloc(1 * sizeof(struct inputObj)); 
                parseInput(inputBuffer,Obj); // parse command line
                runCommand(Obj); // run command
                freeInputObj(Obj);
            }
            else{
                continue;
            }
        }
    }while(true);
}
/****************************************************************
 * this function helps parseInput to see if there is a specail 
 *  char and returns a bool 
*****************************************************************/
bool is_specialChar(char *str){
    bool isSpecial = false;
    if(str == NULL){  // check value isnt null, dont want a seg fault
        return true;
    }
    if(str[0] == '&'){// checks for bg.
        isSpecial = true;
    }
    else if(str[0] == '<'){ // check for input char
        isSpecial = true;
    }
    else if(str[0] == '>'){ // check for output char
        isSpecial = true;
    }
    else if(str[0] == '#'){ // check for command char
        isSpecial = true;
    }
    return isSpecial;
}

/*****************************************************************
 * this function is pharse the input and load it in the struct 
*****************************************************************/
void parseInput(char* inputBuffer,struct inputObj* Obj){
    char Buffer[1028];
    char *InputFileName;
    char *OutputFileName;
    char *temp;
    Obj->NumArgs = 0;
    inputBuffer[strlen(inputBuffer) -1] = '\0'; // removes the \n
    if(inputBuffer[strlen(inputBuffer) -1] == '&'){ // check for bg enabled
        Obj->Background = true; //background enabled 
        inputBuffer[strlen(inputBuffer) -1] = '\0'; // remove char.
    }
    else{
        Obj->Background = false; //background disabled 
    }
    //command
    memset(Buffer,'\0',sizeof(Buffer)); //clears the  Buffer
    strcpy(Buffer,inputBuffer); //copies the  buffer
    strtok(Buffer," "); //grab only command part of input
    strcpy(Obj->Command,Buffer); //takes command place in new obj
    //InputFile Name
    memset(Buffer,'\0',sizeof(Buffer)); 
    strcpy(Buffer,inputBuffer);
    InputFileName = strstr(Buffer,"<"); //grab everything after <
    if(InputFileName != NULL){
        memmove(InputFileName, InputFileName+2, strlen(InputFileName)); //place everything but "< " in string
        strtok(InputFileName," "); // cuts off excess
        InputFileName[strlen(InputFileName)] = '\0'; // adds end char
        strcpy(Obj->InputFile,InputFileName);
    }
    //OutputFile Name: 
    memset(Buffer,'\0',sizeof(Buffer)); //clears the buffer 
    strcpy(Buffer,inputBuffer); //copies the buffer 
    OutputFileName = strstr(Buffer,">"); //grab everything after ">"
    if(OutputFileName != NULL){ //checks for output file name 
        memmove(OutputFileName, OutputFileName+2, strlen(OutputFileName));//place everything but "> " chars in string
        strtok(OutputFileName," "); //cuts off excess
        OutputFileName[strlen(OutputFileName)] = '\0'; //adds  end char
        strcpy(Obj->OutputFile,OutputFileName);
    }
    //arguments
    memset(Buffer,'\0',sizeof(Buffer)); //clears the buffer again 
    strcpy(Buffer,inputBuffer); //copies the string 
    strtok(Buffer," "); //everything before first space
    temp = strtok(NULL,""); //grabs everyhting after first space
    if(is_specialChar(temp) == false){ //checks if there are any args
        strcpy(Buffer,temp);
        strtok(Buffer,"<>&#"); //grabs everything before args
        strtok(Buffer," "); //cuts the  space
        Obj->Arguments[0] = Buffer; //the first arg
        Obj->NumArgs = 1;
        temp = strtok(NULL," "); //the next arg
        while(temp != NULL){
            Obj->Arguments[Obj->NumArgs] = temp;//input all args into list
            Obj->NumArgs++;
            temp = strtok(NULL," ");
        }
        Obj->Arguments[Obj->NumArgs] = strtok(NULL, ""); //grabs last arg     
    }
}

//NUMBER THREE EXPANSION OF VARIABLE ... PROCESS ID  

//NUMBER FOUR BUILD IN FUNCTIONS 
/*****************************************************************
 * this function is to exit the smallsh
*****************************************************************/
void command_exit(){
    for(int i = 0; i < pidStack.pid_val + 1; i++){
        kill(pidStack.backgroundPids[i], SIGINT); // interrupt all bg pids.
    }
}
/*****************************************************************
 * this function either:
 * A) changes directory from HOME enviorment variables  
 * B) take an argument of the path to directory to change to 
*****************************************************************/
int command_cd(char* inputBuffer){
    char* homeDirectPath = getenv("HOME"); //gets the home path
    char NewPath[1028];
    inputBuffer[strlen(inputBuffer) -1] = '\0';
    if(strcmp(inputBuffer,"cd") == 0){
        if(chdir(homeDirectPath) != 0){ // checks if cannot find directory
            printf("Directory:%s not found.\n",homeDirectPath);
            return 1;
        }
        return 0;
    }
    memset(NewPath,'\0',sizeof(NewPath));
    strtok(inputBuffer," "); // this removing spacing
    strcpy(inputBuffer,strtok(NULL,""));
    if(inputBuffer[0] == '/'){
        sprintf(NewPath,"%s%s",homeDirectPath,inputBuffer); // goes to a specifed directory from home directory
    }
    else if(strcmp(inputBuffer,"..") == 0){ // goes back a folder/directory
        strcpy(NewPath,inputBuffer);
    }
    else if(strcmp(inputBuffer,"~") == 0){ // goes back a folder/directory 
        strcpy(NewPath,homeDirectPath);
    }
    else if(inputBuffer[0] == '.' && inputBuffer[1] == '/'){ // the current directory
        sprintf(NewPath,"%s",inputBuffer);
    }
    else{
        sprintf(NewPath,"%s",inputBuffer); // goes to directory from home
    }
    if(chdir(NewPath) != 0){ // cannot find directory
        printf("Directory:%s not found.\n",NewPath);
        return 1;
    }
    return 0;
}
/*****************************************************************
 * this function prints the exit status or the terminiting signal 
 * of the last foreground process ran by the shell 
*****************************************************************/
void command_status(){
    //run before foreground return 0 
    //3 build in do not count as foreground so this should ignore all the built in 
    //this is in runshell i didnt end up using this 

}

//NUMBER FIVE EXICUTING OTHER COMMANDS 
/*****************************************************************
 * this function creates a list of arguments for execvp
*****************************************************************/                                      
void argList(struct inputObj* Obj,char** Args){
    int i;
    Args[0] = Obj->Command; // first arg is the command itself
    for(i = 0; i < Obj->NumArgs; i++){
        if(getenv(Obj->Arguments[i]) != NULL){
            Args[i+1] = getenv(Obj->Arguments[i]); //this add all args
        }
        else if(strcmp(Obj->Arguments[i],"$$") == 0){
            sprintf(Args[i+1],"%d",getpid());
        }
        else{
            Args[i+1] = (Obj->Arguments[i]);
        }
    }
    Args[i+1] = NULL;  // NEED THIS TO WORK, null at the end
}

/*****************************************************************
 * this function creates a redirection of the input and the output 
*****************************************************************/                   
void Redirects(struct inputObj* Obj){
    int InputFileDescriptor = STDIN_FILENO;
    int OutputFileDescriptor = STDOUT_FILENO;
    if(Obj->InputFile[0] != '\0'){ //this checks if inputs are active
        InputFileDescriptor = open(Obj->InputFile,O_RDONLY); // opens the  file
        if(InputFileDescriptor < 0){ //if not found then exit and prints msg
            printf("File could not be found.\n");
            exit(1);
        }
        dup2(InputFileDescriptor,0); //changes input redirection
        close(InputFileDescriptor); //this closes the file
    }
    if(Obj->OutputFile[0] != '\0'){ //check if outputs are actve
        OutputFileDescriptor = open(Obj->OutputFile,O_WRONLY | O_CREAT | O_TRUNC,0644); //creates new file or edits it 
        if(OutputFileDescriptor < 0){ //this check for error
            printf("Error opening or creating file."); //error msg
            exit(1);
        }
        dup2(OutputFileDescriptor,1);//now changes output directions
        close(OutputFileDescriptor); //closeing output file 
    }
}

/*****************************************************************
 * this function frees input functions 
*****************************************************************/ 
void freeInputObj(struct inputObj* Obj){
    Obj->Background = false; // resets the background 
    //clear all fields.
    memset(Obj->InputFile,'\0',sizeof(Obj->InputFile));
    memset(Obj->OutputFile,'\0',sizeof(Obj->OutputFile));
    memset(Obj->Command,'\0',sizeof(Obj->Command));
    free(Obj);//witout this the signal will be triggered 
}

//global 
bool onlyForeground = false;
/*****************************************************************
 * this function creates a child forked for a commnad
*****************************************************************/   
void runCommand(struct inputObj* Obj){
    pid_t pid = fork();
    char *ArgList[512];
    int processStatus;
    switch(pid){
        case -1: //this for an error
            printf("Something went wrong with fork().\n");
            exit(1);
            break;

        case 0: //this is for the child
            Redirects(Obj);             
            argList(Obj,ArgList);
            execvp(Obj->Command, ArgList); //runs the command
            printf("Command not found.\n");
            exit(1);
            break;

        default: //this is for the parent
            if(Obj->Background == true && onlyForeground == false){ //setup bg or non bg.
                addPid(pid); // add to background to stack
                printf("Background Pid is %d\n",readPid());
            }
            else{
                waitpid(pid,&processStatus,0); // hang the shell is bg inactive
                lastForegroundStatus = processStatus;
            }
            break;
    }
}

//PART EIGHT
/*****************************************************************
 * this function is a signal handler for ^z
*****************************************************************/  
void TrapStopSignal(int sig){
    if(onlyForeground == false){
        char* message = ("\nEntering foreground-only mode (& is now ignored)\n"); //enabling foreground mode
        write(STDOUT_FILENO, message, 50);
        onlyForeground = true; //change to global varible
    }
    else{
        char* message = "\nExiting foreground-only mode\n"; //exiting the foreground mode
        write(STDOUT_FILENO, message, 31);
        onlyForeground = false; //change to global varible
    }
}

/*****************************************************************
 * this function is inspired from following link:
 * http://stackoverflow.com/questions/2377811/tracking-the-death-of-a-child-process
 * it is the sibal handler for a child process ending aka the death
 *  of a child
*****************************************************************/  
void TrapChildSignal(int sig){
    pid_t childPid;
    int childStatus;
    int i;
    for(i = 0;i < pidStack.pid_val + 1;i++){ // find pid that exited.
        childPid = waitpid(pidStack.backgroundPids[i],&childStatus,WNOHANG);
        if((childStatus == 0 || childStatus == 1) && childPid != 0 ){ // if exited or errored on exit.
            fprintf(stdout,"\nBackground pid %d is done: exit value %d\n",childPid,childStatus);
            removePid(childPid);
        }
        else if(childPid != 0){ //checks if other signals
            fprintf(stdout,"\nBackground pid %d is done: terminated by signal %d\n", childPid, childStatus);
            removePid(childPid);
        }
    }   
}

/*****************************************************************
 * this function is a signal handler for ^c in a foreground process
*****************************************************************/  
void TrapTermSignal(int sig){
    printf("\nterminated by signal %d\n",sig); 
}

/*****************************************************************
 * this function acts as a switch for foreground mode
 * if a program returns a stop signals
*****************************************************************/  
void is_bgMode(){
    if(WTERMSIG(lastForegroundStatus) == 11 && onlyForeground == true){ // if signal is stop and fg true switch fg
        printf("\nExiting foreground-only mode\n");
        onlyForeground = false;
    }
    else if(WTERMSIG(lastForegroundStatus) == 11 && onlyForeground == false){ // if signal is stop and fg false switch fg 
        printf("\nEntering foreground-only mode (& is now ignored)\n");
        onlyForeground = true;
    }
}

