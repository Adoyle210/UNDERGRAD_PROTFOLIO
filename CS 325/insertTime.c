/****************************************************
 * This is for insertTime
 * this program records the time for insertsort
 * used https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
 * to create rand ints for the arrays 
 ****************************************************/
#include <stdio.h> //standard c library 
#include <stdlib.h>
#include <math.h>
#include <time.h>

//list of functions
void insertsort(int list[], int num);
void printList(int list[], int size);

int main(int argc, const char *argv[]){
    int num_sort = 10;  //num of nums in a line
    int i, j, k;
    int upper = 10000; //upper bound for randon num
    int lower = 0; //lower bound for random num
    clock_t start, end;
    double timeTaken;

    srand(time(0)); //starting time for rand 

    for(i = 0; i < 8; ++ i){              
        int *list = (int*)malloc(num_sort * sizeof(int));
        /*****************************************************************
         * this part has been changed to randomly fill in nums for array
        ****************************************************************/
        for(j = 0; j < num_sort; j++){ //loading in array 
            k = (rand() % (upper - lower + 1 )) + lower;
            list[j] = k;
        }

        //sorting array and recording the time 
        start = clock();
        insertsort(list, num_sort);
        end = clock();
        timeTaken = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\nWith n = %d the time is %f seconds\n", num_sort, timeTaken);
        printList(list, num_sort);

        for(j = 0; j < num_sort; j++){ //empty array
            list[j] = 0;
        }

        free(list);
        num_sort += 100;
    }
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