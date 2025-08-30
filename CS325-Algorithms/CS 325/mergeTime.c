/****************************************************
 * This is for mergeTime
 * this program records the time for mergesort
 ****************************************************/
#include <stdio.h> //standard c library 
#include <stdlib.h>
#include <math.h>
#include <time.h>

//list of functions 
void merge(int list[], int left, int mid, int right);
void mergeSort(int list[], int left, int right);
void printList(int list[], int size);


int main(int argc, const char *argv[]){
    int num_sort = 10;  //num of nums in a line
    //array = [50, 500, 600, 700]
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
                        //array[i]
        for(j = 0; j < num_sort; j++){ //loading in array 
            k = (rand() % (upper - lower + 1 )) + lower;
            list[j] = k;
        }

        //sorting array and recording the time 
        start = clock();
        mergeSort(list, 0, num_sort - 1);
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
 * this function is to merge two subarrays created 
 * for merge sorting. the first subarray is the left side
 * the second is the right side
 *****************************************************/
void merge(int list[], int left, int mid, int right){
    int i, j, k;  //declaring vars for looping 
    int leftNum = mid - left + 1; //declaring nums to iterate subarrays 
    int rightNum = right - mid;
    int l[leftNum], r[rightNum];  //creating temp subarrays 

    //filling up subarrays 
    for(i = 0; i < leftNum; i++){
        l[i] = list[left + i];
    }
    for(j = 0; j < rightNum; j++){
        r[j] = list[mid + 1 + j];
    }

    //reset variables 
    i = 0;
    j = 0;
    k = left;

    //mergeing temp list back 
    while (i < leftNum && j < rightNum){
        if(l[i] <= r[j]){
            list[k] = l[i];
            i++;
        }
        else{
            list[k] = r[j];
            j++;
        }
        k++;
    }

    //gets the remaining elements in left and right side
    while(i < leftNum){
        list[k] = l[i];
        i++;
        k++;
    }

    while(j < rightNum){
        list[k] = r[j];
        j++;
        k++;
    }
}

/****************************************************
 * this function is to sort the subarrays 
 *****************************************************/
void mergeSort(int list[], int left, int right){
    if(left < right){
        //get the mid point
        int mid = left +(right - left) / 2;

        //mergsort left and right side
        mergeSort(list, left, mid);
        mergeSort(list, mid + 1, right);

        merge(list, left, mid, right);
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