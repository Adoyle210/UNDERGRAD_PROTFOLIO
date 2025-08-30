/********************************************************************
 * This is for insertsort
 * this program reads the file data.txt and will sort
 * its contants 
 ******************************************************************/
#include <stdio.h> //standard c library 
#include <stdlib.h>
#include <math.h>

//list of functions
void insertsort(int list[], int num);
void printList(int list[], int size);

int main(int argc, const char *argv[]){
    FILE *data;
    int num_lines; //lines in the file
    int num_sort;  //num of nums in a line
    int i, j, k;

    //opens data file and checks for errors 
    if( (data = fopen("data.txt","r")) == NULL){
        printf("Error occured when opening the data.txt file");
        exit(1);
    }

    //FIX FOR NUM OF LINES
    //loop till end of file
    while(1 == 1){   
        num_sort = 0;
        if(feof(data)){
            break;
        }                    
        //read number up until space 
        fscanf(data, "%d", &num_sort);
        // printf("\ngot lines: %d \n", num_sort);
        //setting up array
        int *list = (int*)malloc(num_sort * sizeof(int));

        for(j = 0; j < num_sort; j++){ //loading in array 
            fscanf(data, "%d", &k);
           // printf(" %d ", k);
            list[j] = k;
        }

        //sorting array
        insertsort(list, num_sort);
        printList(list, num_sort);

        for(j = 0; j < num_sort; j++){ //empty array
            list[j] = 0;
        }
        free(list);

    }

    //closing file 
    fclose(data); 

    return 0;
}

/****************************************************
 * this functions sorts the list of numbers using 
 * insertion 
*****************************************************/
void insertsort(int list[], int num){
    int i, j, k;
    for(i = 1; i < num; i ++){
        k = list[i];
        j = i - 1;

        //moves elements that are greater then key up one spot
        while(j >= 0 && list[j] > k){
            list[j+1] = list[j];
            j -= 1;
        }
        list[j + 1] = k;
    }
}

/****************************************************
 * this function prints the sorted list 
*****************************************************/
void printList(int list[], int size){
    for(int i = 0; i < size; i++){
        printf("%d ", list[i]);
    }
    printf("\n");
}