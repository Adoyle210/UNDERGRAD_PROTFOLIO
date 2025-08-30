/****************************************************************************
 * Assignment two: Knapsack algorithm
 * By: Alexis Doyle
 * Description: this is to test Knapsack DP vs Recursive using randomly nums
 * source: https://www.educative.io/edpresso/what-is-the-knapsack-problem
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//Functions for the program:
int isMax(int a, int b);
int knapSackRecursive(int W, int wt[], int val[], int n);
int knapSackDP(int W, int wt[], int val[], int n);

int main(){
    int i, j, k, max1, max2;
    int n = 10;
    int w = 100;
    int upper = 100; //upper bound for randon num
    int lower = 0; //lower bound for random num
    clock_t start, end;
    double timeTaken1, timeTaken2;

    for(i = 0; i < 8; ++i){
        //allocate space for the two arrays:
        int *val = (int*)malloc(n * sizeof(int)); 
        int *wt = (int*)malloc(n * sizeof(int));

        //fill up the two arrays:
        for (j = 0; j < n; j++){
            k = (rand() % (upper - 26 )) + lower;     //Should this be lower??
            val[j] = k;
        }
        for (j = 0; j < n; j++){
            k = (rand() % (upper - lower + 1 )) + lower;
            wt[j] = k;
        }
        
        //getting times for knapsack:
        start = clock();
        max1 = knapSackDP(w, wt, val, n);
        end = clock();
        timeTaken1 = ((double) (end - start)) / CLOCKS_PER_SEC;

        start = clock();
        max2 = knapSackRecursive(w, wt, val, n);
        end = clock();
        timeTaken2 = ((double) (end - start)) / CLOCKS_PER_SEC;

        printf("N = %d w = %d Rec Time = %f DP time = %f Max Rec = %d Max DP = %d \n", n, w, timeTaken2, timeTaken1, max2, max1);


        for(j = 0; j < n; j++){ //empty array
            val[j] = 0;
            wt[j] = 0;
        }
        free(val);
        free(wt);

        n += 5;
        w += 10;
    }


    
    /*int val[] = { 60, 100, 120 };
    int wt[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    printf("%d", knapSack(W, wt, val, n));*/ //w is capacity and n is size
    return 0;
}
 
/****************************************************************************
 * IsMax: is a helper funtion for the knapsack algorthm
 * it's job is to test two intergers and see which is the max
***************************************************************************/
int isMax(int a, int b){ 
    if(a > b){
        return a;
    }
    else{
        return b;
    }
}
 
/****************************************************************************
 * knapSackRecursive: this function follows the knapsack algorthm using two arrays
 * wt[] and val[] as suggested in the homework 
 * w is the capacity of wt and val and n is the size
***************************************************************************/
int knapSackRecursive(int W, int wt[], int val[], int n)
{
    // Base Case
    if (n == 0 || W == 0){
        return 0;
    }
    // If weight of the nth item is more than
    // Knapsack capacity W, then this item cannot
    // be included in the optimal solution
    if (wt[n - 1] > W){
        return knapSackRecursive(W, wt, val, n - 1);
    }
    // Return the maximum of two cases:
    // (1) nth item included
    // (2) not included
    else{
        return isMax(
            val[n - 1]
                + knapSackRecursive(W - wt[n - 1],
                           wt, val, n - 1),
           knapSackRecursive(W, wt, val, n - 1));
    }
}

/****************************************************************************
 * knapsackDP: this function follows dynnamic programing for the knapsack algorthm 
 * it using two arrays wt[] and val[] as suggested in the homework 
 * w is the capacity of wt and val and n is the size 
***************************************************************************/
int knapSackDP(int W, int wt[], int val[], int n){
    // can be put in a knapsack of capacity W
    int i, w;
    int K[n + 1][W + 1];
 
    // Build table K[][] in bottom up manner
    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= W; w++)
        {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (wt[i - 1] <= w)
                K[i][w] = isMax(val[i - 1]
                          + K[i - 1][w - wt[i - 1]],
                          K[i - 1][w]);
            else
                K[i][w] = K[i - 1][w];
        }
    }
 
    return K[n][W];
}

 