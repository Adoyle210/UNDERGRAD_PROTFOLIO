/****************************************************
 * This is for mergesort
 * this program reads the file data.txt and will sort
 * its contants 
 * used https://www.tutorialspoint.com/cprogramming/c_file_io.htm for loading in file 
 * used https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/ for mem
 ****************************************************/
#include <stdio.h> //standard c library 
#include <stdlib.h>

//list of functions 
void merge(int list[], int left, int mid, int right);
void mergeSort(int list[], int left, int right);
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
        mergeSort(list, 0, num_sort - 1);
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