/****************************************************************************
 * Assignment Three: Last to start Algo
 * By: Alexis Doyle
 * Description: this runs the greedy last to start algo
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

//Functions for the program: 
void swap(int *xp, int *yp);
void MaxActs(int s[], int f[], int log[], int n);
void bubbleSort(int arr[], int arr2[], int arr3[], int n);

int main(){
    FILE *Act; //declarion for file to be open
    int i, j, k, l, m;
    int set = 1; //keeps track of the number of sets
    if((Act = fopen("act.txt", "r")) == NULL){
        printf("Error occured when opening the data.txt file");
        exit(1);
    }

    while(1 == 1){
        k = 0; //number in each set
        if(feof(Act)){
            break;
        } 
        printf("Set %d\n", set); //printing set we are on
        set += 1;

        fscanf(Act, "%d", &j);  // getting amount in the set

        int *start = (int*)malloc(j * sizeof(int));
        int *finish = (int*)malloc(j * sizeof(int));
        int *log = (int*)malloc(j * sizeof(int));

        for(i = 0; i < j; i++){ //cycling in the set
            fscanf(Act, "%d", &k);
            log[i] = k;
            //printf(" %d ", k);
            fscanf(Act, "%d", &l);
            start[i] = l;
            //printf(" %d ", l);
            fscanf(Act, "%d", &m);
            finish[i] = m;
            //printf(" %d  \n", m);
        }

        bubbleSort(start, finish, log, j);

        //freeing up memory
        for(i = 0; i <j; i++){ //empty array
            start[i] = 0;
            finish[i] = 0;
            log[i] = 0;
        }
        free(start);
        free(finish);
        free(log);
    }
}


/****************************************************************************
 * Swap: This function is a helper function to bubble sort 
 *       it swaps two ints in an array
***************************************************************************/
void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
  
/****************************************************************************
 * Bubble sort: This function used a basic bubble sort algo that is O(n^2)
 *              it sorts all 3 arrays (start, finish and the log)
***************************************************************************/
void bubbleSort(int arr[], int arr2[], int arr3[], int n){
   int i, j;
   for (i = 0; i < n-1; i++){    
       for (j = 0; j < n-i-1; j++){
           if (arr[j] > arr[j+1]){
              swap(&arr[j], &arr[j+1]);
              swap(&arr2[j], &arr2[j+1]);
              swap(&arr3[j], &arr3[j+1]);
            }
        }
    }

    //this is calling the max activiy function do the greedy for the activies 
    int w = sizeof(&arr)/sizeof(arr[0]);
    MaxActs(arr, arr2, arr3, n);

}


/****************************************************************************
 * MaxActs: this function is to do the last to start algo and print the
 *          results to match the solution.txt
***************************************************************************/
void MaxActs(int s[], int f[], int log[], int n){
    int i, j;
    int count = 0;

    //it runs through once to get the count and bc we don't believe in efficency 
    //just results when it comes to homework 
    i = 0;
    for(j = 1; j < n; j++){
        if (s[j] >= f[i]){
            count += 1;
            i = j;
        }
    }

    printf("Maximum number of activities = %d \n", count);
 
    //the following is the second time it is running though the algo
    // The first activity always gets selected
    i = 0;
    //printf("%d ", i);
 
    // Consider rest of the activities
    for (j = 0; j < n; j++){
      // If this activity has start time greater than or
      // equal to the finish time of previously selected
      // activity, then select it
        if (s[j] >= f[i]){
            printf ("%d ", log[i]);
            i = j;
        }
    }
    printf ("\n ");
}