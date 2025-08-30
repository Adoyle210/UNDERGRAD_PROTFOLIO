#include "dec_client.h"

// error function used for reporting issues
/*********************************************************************************************************************************
* used: http://stackoverflow.com/questions/28239081/reading-in-a-binary-file-in-c-then-matching-data-from-the-file-to-what-i-have-r
*       http://www.linuxhowtos.org/C_C++/socket.htm
* 	    https://github.com/rocko-rocko/Application-Layer-File-Transfer-Protocol/blob/master/cli/client.c
* 	    http://www.linuxquestions.org/questions/showthread.php?p=4714903
*       https://man7.org/linux/man-pages/man3/bzero.3.html
************************************************************************************************************************************/
int main(int argc, char *argv[]) {
  if (argc != 4){ //check args 
		printf("usage: dec_client plaintext key port\n");
		exit(1);
	}
  int socketFD, charsWritten, charsRead;
  int portNum = atoi(argv[3]); 
  struct sockaddr_in addr_remote;
  struct hostent* HostInfo;
  char* buffer, *plaintext, *key;
  //allocate mem/ set up for buffer:
  buffer = malloc(sizeof(char) * BUFFER_SIZE); 
  assert(buffer != 0);
  memset(buffer, '\0', sizeof(buffer));
  //allocate mem/set up for text 
  plaintext = malloc(sizeof(char) * BUFFER_SIZE); 
  assert(plaintext != 0);
  memset(plaintext, '\0', sizeof(plaintext));
  //allocate mem/set up for key 
  key = malloc(sizeof(char) * BUFFER_SIZE); 
  assert(key != 0);
  memset(key, '\0', sizeof(key));
  // set up the server struct:
  memset((char*)&addr_remote, '\0', sizeof(addr_remote)); // clear address struct
  addr_remote.sin_family = AF_INET; // protocol Family
  addr_remote.sin_port = htons(portNum);  // port number
  HostInfo = gethostbyname("127.0.0.1"); //address local host
  if (HostInfo == NULL) { 
    fprintf(stderr, "dec_client: error, no such host error code: %d\n", errno);
    exit(1); 
  }
  memcpy((char*)&addr_remote.sin_addr.s_addr, (char*)HostInfo->h_addr_list[0], HostInfo->h_length); 
  //plaintext:
  char* plaintextName = (char*)argv[1];  //open the files for reading
  FILE* plaintextFD = 0;
  plaintextFD = fopen(plaintextName, "r");
  //key:
  char* keyName = (char*)argv[2];  //open the files for reading
  FILE* keyFD = 0;
  keyFD = fopen(keyName, "r");
  if(plaintextFD != 0 && keyFD != 0) {
    if ((socketFD = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
      fprintf(stderr,"dec_client: error opening socket");
    }
    if (connect(socketFD, (struct sockaddr*)&addr_remote, sizeof(addr_remote)) < 0) {
      fprintf(stderr,"dec_client: error connecting");
    }
    //plaintext:
    getMSG(plaintext, plaintextFD); 
    int plaintextLen = strlen(plaintext);
    //key:
    getMSG(key, keyFD);
    int keyLen = strlen(key);
    int totalSize = plaintextLen + keyLen;
    if(plaintextLen > keyLen) {
      fprintf(stderr, "error: key '%s' is too short\n", keyName);
      exit(1);
    }
    //set up params for plaintext
    char params[256];
    memset(params, '\0', 256);
    sprintf(params, "%d d ", totalSize);
    sendMSG(params, socketFD); //send param
    sendMSG(plaintext, socketFD); //send plaintext
    sendMSG(key, socketFD); //send key
    if(plaintextFD != NULL) {
      fclose(plaintextFD);
    }
    if(keyFD != NULL) {
      fclose(keyFD);
    }
    //get return message from server
    do {
      memset(buffer, '\0', sizeof(buffer)); // clear buff
      charsRead = recv(socketFD, buffer, sizeof(buffer) - 1, 0); // read data 
      if (charsRead < 0) {
	      fprintf(stderr,"dec_client: error reading from socket");
      }
      //printf("dec_client: from server: \"%s\"\n", buffer);
      printf("%s", buffer);
    } while(charsRead > 0); //ends when conection closes
    printf("\n");
    close(socketFD); // Close the socket
  }
  //free mem
  MustFree(buffer);
  MustFree(plaintext);
  MustFree(key);
  return 0;
}

/*********************************************************************************************************************************
 * def: frees data 
*********************************************************************************************************************************/
void MustFree(char* mustFree){
  if(mustFree != 0) {
    free(mustFree);
    mustFree = 0;
  }
}

/*********************************************************************************************************************************
 * def: reads file into buffer
*********************************************************************************************************************************/
void getMSG(char* buffer, FILE* fp) {
  memset(buffer, '\0', sizeof(buffer)); // lear buff
  if(fgets(buffer, (BUFFER_SIZE - 1), fp) != NULL) { //loop if buff filled 
    for(int i = 0; i < BUFFER_SIZE; ++i) {
      if(buffer[i] == '\n' || buffer[i] == '\0') { //break at end 
	      break;
      }
      else if(!isalpha(buffer[i]) && buffer[i] != ' ') {
	      fprintf(stderr, "dec_client: error Plaintext contained invalid character\n");
	      exit(1);
      }
    }  
  }
}


/*********************************************************************************************************************************
 * def: send buff to the server
*********************************************************************************************************************************/
void sendMSG(char* buffer, int socketFD) {
  int charsWritten = 0;
  int messageLength = strlen(buffer);
  int totalCharsWritten = 0;
  while(totalCharsWritten < messageLength) {
    charsWritten = send(socketFD, buffer, messageLength, 0);
    if (charsWritten < 0) {
      fprintf(stderr,"dec_client: error writing to socket");
    }
    if (charsWritten < messageLength) {
      printf("dec_client: WARNING: Not all data written to socket!\n");
    }
    totalCharsWritten += charsWritten;
  }
}