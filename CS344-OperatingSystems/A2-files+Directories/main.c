/********************************************************
 * this is where the main function is located and it runs 
 * the whole program 
*********************************************************/
#include "process.h"

int choice_check(int c){
    int choice = 0;
    int check = c + 1;
    while(choice <= 0 || choice >= check ){
        printf("Enter a choice 1 or %d: ", c);
        scanf("%d", &choice);
        printf("\n");
    }
    return choice;
}

int main(int argc, const char *argv[]){
    int choice = 0;
    int error = 0; //keep track if 3 has an error 
    do{
        printf("1. Select file to process\n 2. Exit the program\n");
        choice = choice_check(2);
        while(choice == 1 && error == 0){
            printf("Which file you want to process? \n Enter 1 to pick the largest file \n Enter 2 to pick the smallest file \n Enter 3 to specify the name of a file \n");
            choice = choice_check(3);
            if(choice == 1){
                largest();// large
            }
            else if(choice == 2){
                smallest();// small
            }
            else if(choice == 3){
                error = userChoice();// user choice 
            }
            choice = 0; //reset choice to reset loop 
            if(error == 0){
                choice = 1;
            }
        }
        error = 0;
    }while(choice != 2);

}
