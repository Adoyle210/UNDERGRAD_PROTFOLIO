#include "processor.h"
//Globals:
int STOP = 1; //for the current status of if stop has appeared
int STOP1 = 1;
int STOP2 = 1;
int STOP3 = 1;
int loop = 1;

// Initialize the mutex:
pthread_mutex_t mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_3 = PTHREAD_MUTEX_INITIALIZER;

//Initialize conditions: 
pthread_cond_t full_1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t full_2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t full_3 = PTHREAD_COND_INITIALIZER;

/***********************************************************
* def: This function is for checking the status and if 
*      the line says STOP only then the threads will stop
***********************************************************/
int check_status(char file[]){
  char status[5] = "STOP\n";
  return(strcmp (file, status));
}
/***********************************************************
* def: This function is for the first thread, it reads 
*      the lines 
***********************************************************/
void *readLines(void* args){ 
  while(STOP != 0){ 
    char file[1000];
    fflush(stdin); //clear buffer 
    fgets(file,sizeof(file),stdin); //getting command line
    STOP = check_status(file);
    if(STOP != 0){
      //adding to buffer:
      pthread_mutex_lock(&mutex_1);
      struct buffer* curr_line = (struct buffer*) args;
      for(int i = 0; i < strlen(file); i++){ 
        curr_line->file[curr_line->index] = file[i]; 
        //printf("%c",curr_line->file[curr_line->index]);
        curr_line->index ++;
      }
      curr_line->count += 1;
      pthread_cond_signal(&full_1);
      pthread_mutex_unlock(&mutex_1);
      //printf("READ LINES\n");
      //loop ++;
    }
  }
  //pthread_exit(args);
  return NULL;
} 

/***********************************************************
* def: This function is like the consumer for buffer 1
* source: inspired by from sample 
*          https://replit.com/@cs344/65prodconspipelinec
***********************************************************/
struct buffer get_buff_1(void *args){
  // Lock the mutex before checking if the buffer has data
  struct buffer temp;
  struct passTwo* both = (struct passTwo*) args;
  pthread_mutex_lock(&mutex_1);
  struct buffer* curr_line = both->producer;
  while (curr_line->count == 0)
    //printf("Testing \n");
    // Buffer is empty. Wait for the producer to signal that the buffer has data
    pthread_cond_wait(&full_1, &mutex_1);
  strcpy(temp.file, curr_line->file);
  curr_line->count -= 1;
  temp.count = curr_line->count;  
  temp.numchar = strlen(curr_line->file);
  pthread_mutex_unlock(&mutex_1);
  //printf("GET BUFF1\n");
  return temp; // Return the struct
}

/***********************************************************
* def: This function is for the second thread, it deals
*       with line separators and replaces them with spaces
***********************************************************/
void *lineSeparator(void* args){ 
  while(STOP1 != 0){
    struct buffer curr_line = get_buff_1(args);
    STOP1 = check_status(curr_line.file);
    //if(STOP1 != 0){
      //looping for line separators: 
      for(int i = 0; i < curr_line.numchar; i++){ 
        //printf("%c",curr_line.file[i]);
        if(curr_line.file[i] == '\n'){
          curr_line.file[i] = ' ';
        }
      }
      pthread_mutex_lock(&mutex_2); 
      struct passTwo* both = (struct passTwo*) args;
      struct buffer*  b2 = both->consumer;
      strcpy(b2->file, curr_line.file);
      b2->numchar = curr_line.numchar;
      b2->index = curr_line.index;
      b2->count += 1;
      pthread_cond_signal(&full_2);
      pthread_mutex_unlock(&mutex_2);
      //storing temp in buffer 2 
      //printf("LINE SEP.\n");
    //}
  }
  //pthread_exit(args);
  return NULL;
}

/***********************************************************
* def: This function is like the consumer for buffer 2
* source: inspired by from sample 
*          https://replit.com/@cs344/65prodconspipelinec
***********************************************************/
struct buffer get_buff_2(void *args){
  // Lock the mutex before checking if the buffer has data
  struct buffer temp;
  pthread_mutex_lock(&mutex_2);
  struct passTwo* both = (struct passTwo*) args;
  struct buffer* curr_line = both->producer;
  while (curr_line->count == 0)
    // Buffer is empty. Wait for the producer to signal that the buffer has data
    pthread_cond_wait(&full_2, &mutex_2);
  strcpy(temp.file, curr_line->file);
  curr_line->count -= 1;
  temp.count = curr_line->count;  
  temp.numchar = curr_line->numchar;
  pthread_mutex_unlock(&mutex_2);
  //printf("GET BUFF2\n");
  return temp; // Return the struct
}

/***********************************************************
* def: This function is for the third thread, it deals
*       with ++ and replaces them with ^ 
***********************************************************/
void *plusSign(void* args){
  while(STOP2 != 0){ 
    char temp; //holds characters to replace
    //struct passTwo* both = (struct passTwo*) args;
    //struct buffer*  b2 = both->producer;
    struct buffer curr_line = get_buff_2(args);
    STOP2 = check_status(curr_line.file);
    //if(STOP2 != 0){
      curr_line.count -=1;
      for(int i = 0; i < curr_line.numchar; i++){ 
        if(curr_line.file[i] == '+' && curr_line.file[i+1] == '+'){
          curr_line.file[i] = '^';
          for(int j = i + 1; j < curr_line.numchar; j++){
            temp = curr_line.file[j + 1];
            curr_line.file[j] = temp;
            curr_line.file[j + 1] = curr_line.file[j + 2];
          }
          curr_line.numchar --; //subtract because char deleted
        }
        //printf("%c", curr_line.file[i]);
      }
      //printf("PLUS SIGN\n");
      pthread_mutex_lock(&mutex_3); 
      struct passTwo* both = (struct passTwo*) args;
      struct buffer*  b3 = both->consumer;
      strcpy(b3->file, curr_line.file);
      b3->numchar = curr_line.numchar;
      b3->index = curr_line.index;
      b3->count += 1;
      pthread_cond_signal(&full_3);
      pthread_mutex_unlock(&mutex_3);
    //}
  }
  //pthread_exit(args);
  return NULL;
}
/***********************************************************
* def: This function is like the consumer for buffer 3
* source: inspired by from sample 
*          https://replit.com/@cs344/65prodconspipelinec
***********************************************************/
struct buffer get_buff_3(void *args){
  // Lock the mutex before checking if the buffer has data
  struct buffer temp;
  pthread_mutex_lock(&mutex_3);
  struct buffer* curr_line = (struct buffer*) args;
  while (curr_line->count == 0)
    // Buffer is empty. Wait for the producer to signal that the buffer has data
    pthread_cond_wait(&full_3, &mutex_3);
    sleep(2);
  strcpy(temp.file, curr_line->file);
  temp.count = curr_line->count - 1;  
  temp.numchar = curr_line->numchar;
  pthread_mutex_unlock(&mutex_3);
  //printf("GET BUFF3\n");
  return temp;   // Return the struct 
}

//Globals
int new_line = 80;
int index_print = 0;
/***********************************************************
* def: This function is for the fourth thread, it deals
*       with processing data to standard output as lines of 
*       exactly 80 characters
***********************************************************/
void *output(void* args){
  while(STOP3 == 1){
    struct buffer curr_line = get_buff_3(args);
    if(curr_line.numchar > new_line){
      for(int i = index_print; i <= new_line; i++){ 
        index_print ++;
        printf("%c", curr_line.file[i]);
        if(i == new_line){
          printf("\n");
          new_line += 80;
        }
        if(curr_line.numchar < new_line && STOP != 0){
          i = new_line;
        }
        if(i == curr_line.numchar && STOP == 0){
          STOP3 = 0;
          break;
        }
        else if(i == curr_line.numchar){
          i = new_line;
        }
      }
    }
    /*else if(index_print < curr_line.numchar && STOP == 0){
      for(int i = index_print; i <= curr_line.numchar; i++){ 
        index_print ++;
        printf("%c", curr_line.file[i]);
      }
    }*/
  }
  pthread_exit(args);
  /*while(STOP3 == 1){
    if(STOP == 0){
      struct buffer curr_line = get_buff_3(args);
      int new_line = 80;
      for(int i = 0; i < curr_line.numchar; i++){ 
        printf("%c", curr_line.file[i]);
        if(i == new_line){
          printf("\n");
          new_line += 80;
        }
      }
      STOP3 = 0;
    }
  }*/
  //printf("OUTPUT\n");
  return NULL;
}  

/***********************************************************
* def: This function is for freeing memory 
***********************************************************/
/*void free_mem(void* args){
  struct buffer buff = get_buff_3(args);
  int len = strlen(buff.file);
  for(int i = 0; i < len; i ++){
    free(&buff.file[i]);
  }
  free(&buff.index);
  free(&buff.numchar);
  free(&buff.count);
}*/

int main(int argc, char *argv[]){
    srand(time(0));
    struct buffer b1;
    //b1.count = 0;
    struct buffer b2;
    //b2.count = 0;
    struct buffer b3;
    //b3.count = 0;
    //Initializeing pointers to pass two structs to threads
    struct passTwo b1b2; 
    b1b2.producer = &b1; 
    b1b2.consumer = &b2;
    struct passTwo b2b3;
    b2b3.producer = &b2;
    b2b3.consumer = &b3;
    //createing the four threads: 
    pthread_t thread_one, thread_two, thread_three, thread_four;
    pthread_create(&thread_one, NULL, readLines, (void*) &b1);
    pthread_create(&thread_two, NULL, lineSeparator, (void*) &b1b2);
    pthread_create(&thread_three, NULL, plusSign, (void*) &b2b3);
    pthread_create(&thread_four, NULL, output, (void*) &b3);
    //termating threads: 
    pthread_join(thread_one, NULL);
    pthread_join(thread_two, NULL);
    pthread_join(thread_three, NULL);
    pthread_join(thread_four, NULL);
    
    /*free_mem(&b1);
    free_mem(&b2);
    free_mem(&b3);
    free(&b1);
    free(&b2);
    free(&b3);
    free(&b1b2);
    free(&b2b3);*/
    exit(EXIT_SUCCESS);
    return 0;
}