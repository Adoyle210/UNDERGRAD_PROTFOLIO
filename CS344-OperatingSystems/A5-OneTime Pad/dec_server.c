#include "dec_server.h"

int main(int argc, char *argv[]){
    if (argc < 2){
		printf("usage: dec_server port\n");
		exit(1);
	}
    //declaring vars: 
    int sockfd, newsockfd;
    int portNum = atoi(argv[1]);
    socklen_t sin_size;
    char* buffer;
    struct sockaddr_in addr_local; // server addr
	struct sockaddr_in addr_remote; // client addr
    struct sigaction sa; //for signal 
    //fill the server struct:
    memset((char *)&addr_local, '\0', sizeof(addr_local)); // Clear 
    addr_local.sin_family = AF_INET; // protocol Family
    addr_local.sin_port = htons(portNum); // port number
    addr_local.sin_addr.s_addr = INADDR_ANY; // allowing all connections  
    //set up and check the socket:
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ){ 
		fprintf(stderr, "error: Failed to set up Socket Descriptor. error code: %d\n", errno);
		exit(1);
	}
    //bind to port: 
    if ( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) < 0 ){ 
	    fprintf(stderr, "error: could not binding to port. error code: %d\n", errno);
		exit(1);
	}
    //set up listen for five children: 
    if (listen(sockfd, LISTEN_QUEUE) < 0)	{ // Listen to port
		fprintf(stderr, "error: Failed to listen Port. error code: %d\n", errno);
		exit(1);
	}
    //set the signal handler:
    sa.sa_handler = &wait_for_child; 
    sa.sa_flags = SA_RESTART; 
    //set up buffer
    buffer = malloc(sizeof(char) * BUFFER_SIZE);
    assert(buffer != 0);
    memset(buffer, '\0', sizeof(buffer));
    while(1) {
        sigaction(SIGCHLD, &sa, NULL);  //handle Signals
        if(NumChildren < LISTEN_QUEUE) {
            sin_size = sizeof(addr_remote); //get the size of the address 
            //accept connection from client:
            if ((newsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) < 0)	{  
			    fprintf(stderr, "error: Obtaining new socket descriptor. (errno = %d)\n", errno);
			    exit(1);
		    }
            else { //deals with decryption:
	            pid_t pid;
	            if((pid = fork()) == 0) { //create new child
                    decrypt(buffer, newsockfd); //handles decryption
                    close(newsockfd); //close socket with client  
                    exit(0);
	            }
	            else{
	                close(newsockfd); //close socket with client  
                    //add the pid to the list of running pids
                    children[NumChildren] = pid;
                    NumChildren++;
	            }
            }
        }
    }
    if(buffer != 0) {
        free(buffer);
        buffer = 0;
    }
    close(sockfd); //close socket used for listen
    return 0; 
}

/**************************************************************************
* def: This function is the signal handler to clean up zombie processes
****************************************************************************/
void wait_for_child(int sig) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG); //waiting for child
    if(pid > 0) {
        for(int i = 0; i < LISTEN_QUEUE; ++i) {
            if(children[i] == pid) {
	            children[i] = 0;
	
	            for(int j = i; j < LISTEN_QUEUE - 1; ++j) {
	                children[j] = children[j] + 1;
	            }
	            children[NumChildren - 1] = 0;
	            NumChildren--;
	            break;
            } 
        }
    }
}

/**************************************************************************
 * def: This function handles the decrypting portion and sends it back
****************************************************************************/
void decrypt(char* buffer, int newsockfd){
    int charsRead;
    memset(buffer, '\0', BUFFER_SIZE); 
	//read message from client
	if ((charsRead = recv(newsockfd, buffer, (BUFFER_SIZE - 1), 0)) < 0){
	    fprintf(stderr, "error: while reading from socket error code: %d\n", errno);
	}	
	//parse out the totalChars that is being sent and the client type 'e' or 'd'
	int totalCharsNeeded = getNumChars(buffer);
	char type = getType(buffer);
	if(type == 'e') {
	    fprintf(stderr, "error: enc_client cannot use dec_server error code: %d\n", errno);
	    exit(2);
	} 
	//create a full buffer for the full messages 
    char* fullBuffer = malloc(sizeof(char) * BUFFER_SIZE);
    assert(fullBuffer != 0);
    memset(fullBuffer, '\0', sizeof(fullBuffer));
    strcpy(fullBuffer, buffer);        
    //read in all of the messages from the client and add to fullBuffer
    int totalCharsRead = charsRead; 
    while(totalCharsRead < totalCharsNeeded) {
        memset(buffer, '\0', BUFFER_SIZE);
        //read message from client
        if ((charsRead = recv(newsockfd, buffer, (BUFFER_SIZE - 1), 0)) < 0) {
            fprintf(stderr,"error reading from socket error code: %d\n", errno);
        }

        totalCharsRead += charsRead;
        addToBuffer(fullBuffer, buffer);
    }
    char* messages[2] = {0};
    parseBuffer(fullBuffer, messages);           
    //declare a word, decrypt the message with the key, then store in word
    char* decWord = malloc(sizeof(char) * strlen(messages[0]) + 1);
    assert(decWord != 0);
    memset(decWord, '\0', sizeof(decWord));          
    //decrypt the message
    for(int i = 0; i < strlen(messages[0]); ++i) {
        if(messages[0][i] != '\n') {
            int code = getCharIndex(messages[0][i]) - getCharIndex(messages[1][i]);
            if(code < 0) { code += 27;}
	      	code = code % 27;
            decWord[i] = validChars[code];
        }
    }                
    //send the decrypted word back to client
    int totalCharsWritten = 0;
    int decWordLen = strlen(decWord);
    while(totalCharsWritten < decWordLen) {
        charsRead = send(newsockfd, decWord, decWordLen, 0);
        if (charsRead < 0) {
            fprintf(stderr,"error writing to socket error code: %d\n", errno);
        }
        totalCharsWritten += charsRead;
    }
    //free variables
    if(fullBuffer != 0) {
        free(fullBuffer);
        fullBuffer = 0;
    }
    if(decWord != 0) {
        free(decWord);
        decWord = 0;
    }
    for(int i = 0; i < 2; ++i) {
        if(messages[i] != 0) {
            free(messages[i]);
            messages[i] = 0;
        }
    }
}

/**************************************************************************
* def: This function moves a string down a specfic number and makes the end
*       null or \0
****************************************************************************/
int moveDown(char* str, int len, int index, int shifts) {
    if(str == 0) {return -1;}
    for(int i = 1; i <= shifts; i++) {
        for(int j = index; j < len; j++) {
            str[j] = str[j+1];
            if(str[j] == '\0') {
                break;
            }
        }
        str[len - i] = '\0';
    }
    return 0;
}

/**************************************************************************
 * def: returns the num of chars the client wants to send 
****************************************************************************/
int getNumChars(char* buffer) {
    int space = -1;
    char num[10] = {'\0'};
    for(int i = 0; i < strlen(buffer); ++i) {
        if(buffer[i] == ' ') {
            space = i;
            break;
        }
        num[i] = buffer[i];
    }
    if(space > -1) {
        moveDown(buffer, BUFFER_SIZE, 0, (space + 1));
    }
    int chars = -1;
    sscanf(num, "%d", &chars);
    return chars;
}

/**************************************************************************
 * def: returns client type of e or d and removes it
****************************************************************************/
char getType(char* buffer) {
    for(int i = 0; i < strlen(buffer); ++i) {
        if(buffer[i] == 'e' || buffer[i] == 'd') {
            char type = buffer[i];
            moveDown(buffer, BUFFER_SIZE, i, 2);
            return type;
        }
    }
    return '\0';
}

/**************************************************************************
 * def: returns the possition if the new line
****************************************************************************/
int findNewLine(char* buffer, int start){
    int newLine = -1;
    for(int i = start; i < BUFFER_SIZE; ++i){
        if(buffer[i] == '\n') {
            newLine = i;
            return newLine;
        }
        else if(buffer[i] == '\0'){return -1;}
    }
  return newLine;
}

/**************************************************************************
 * def: returns word from the start index to the end 
****************************************************************************/
char* getFromBuffer(char* buffer, int start, int end){
    char* word = malloc(sizeof(char) * (end + 2));
    assert(word != 0);
    memset(word, '\0', sizeof(word));
    for(int i = 0; i < (end + 1); ++i){
        word[i] = buffer[i + start];
    }
    return word;
}


/**************************************************************************
 * def: split text from the buffer into key words ... parse the buffer
****************************************************************************/
void parseBuffer(char* buffer, char** msgs){
    int previousNewLine = -1;
    for(int i = 0; i < 2; ++i){
        int newLine = findNewLine(buffer, (previousNewLine + 1));
        if(newLine > 0){
            msgs[i] = getFromBuffer(buffer, (previousNewLine + 1), newLine);
        }
        previousNewLine = newLine;
    }
}

/**************************************************************************
 * def: get index from allowed chars
****************************************************************************/
int getCharIndex(char c) {
    for(int i = 0; i < 27; ++i) {
        if(c == validChars[i]){return i;}
    }
     return -100;
}

/**************************************************************************
 * def: adds word to the buffer
****************************************************************************/
void addToBuffer(char* buffer, char* read) {
    int bufIdx = strlen(buffer);
    for(int i = 0; i < strlen(read); ++i) {
        if(bufIdx != sizeof(buffer) - 1) {
            buffer[bufIdx] = read[i];
            bufIdx++;
        }
        else { break;}
    }
}
