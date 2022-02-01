/****************************************************************************
 * Assignment two: Shopping
 * By: Alexis Doyle
 * source: https://www.educative.io/edpresso/what-is-the-knapsack-problem
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>

//Functions for the program:
int isMax(int a, int b);
int knapSackRecursive(int W, int wt[], int val[], int n);
int knapSackDP(int W, int wt[], int val[], int n);
void knapSackDPPart2(int W, int wt[], int val[], int n, int place);

int main(){
    FILE *Shopping; //decalring the file that is to be opened
    int numTest; //the number of test to be done in the file
    int size, numFam, capacity, i, j, k, l;

    //opens shopping file and checks for errors 
    if( (Shopping= fopen("shopping.txt","r")) == NULL){
        printf("Error occured when opening the data.txt file");
        exit(1);
    }
    fscanf(Shopping, "%d", &numTest); //gets the number of test to be conducted 

    for(i = 0; i < numTest; ++i){ //loops based on number of test 
        printf("Test case %d\n", i+1); //prints the test case
        fscanf(Shopping, "%d", &size); //getting size

        //allocating mem to arrays 
        int *val = (int*)malloc(size * sizeof(int)); 
        int *wt = (int*)malloc(size * sizeof(int));

        //filling up both arrays
        for(j = 0; j < size; j++){
            fscanf(Shopping, "%d", &k); 
            val[j] = k;
            fscanf(Shopping, "%d", &k);
            wt[j] = k;
        }

        fscanf(Shopping, "%d", &numFam); //getting the number of family members 

        //looping for family members to get total
        int total = 0;
        for(j = 0; j < numFam; ++j){
            fscanf(Shopping, "%d", &capacity); //gets capacity for the family member
            l = knapSackDP(capacity, wt, val, size);
            total += l;
        }
        printf("Total Price %d\n", total);

        for(j = 0; j < numFam; ++j){
           knapSackDPPart2(capacity, wt, val, size, j + 1);
        }


        
        for(j = 0; j < size; j++){ //empty array
            val[j] = 0;
            wt[j] = 0;
        }
        free(val);
        free(wt);


    }

    /*int val[] = { 60, 100, 120 };
    int wt[] = { 10, 20, 30 };
    int W = 50;
    int n = sizeof(val) / sizeof(val[0]);
    printf("%d", knapSack(W, wt, val, n));*/ //w is capacity and n is size

    fclose(Shopping); //closing the file
    return 0;
}
 
/****************************************************************************
 * IsMax: is a helper funtion for the knapsack algorthm
 * it's job is to test two intergers and see which is the max
***************************************************************************/
int isMax(int a, int b) { 
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
        return isMax(val[n - 1] + knapSackRecursive(W - wt[n - 1], wt, val, n - 1), knapSackRecursive(W, wt, val, n - 1));
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

/****************************************************************************
 * knapsackDPPart2: this function follows dynnamic programing for the knapsack algorthm 
 * it using two arrays wt[] and val[] as suggested in the homework 
 * w is the capacity of wt and val and n is the size 
***************************************************************************/
void knapSackDPPart2(int W, int wt[], int val[], int n, int place){
    // can be put in a knapsack of capacity W
    int i, w, j;
    int K[n + 1][W + 1];
    int counter = 0, k = 0;
    int num[25];
    int selected[25];
 
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

    int total = K[n][W];
    for(i = n - 1; i > 0; i --){
        if(total != K[i-1][W]){
            num[counter] = wt[i];
            //printf("%d ", wt[i]);
            W -= wt[i];
            total -= val[i];
            counter ++;
        }
    }
    if (total != 0){
        num[counter] = wt[0];
    }

    for(i = 0; i < n; i++){
        for(j = 0; j < counter; j++){
            if(val[i] == num[j]){
                selected[k] = i;
                k++;
                break;
            }
        }
    }

    printf("%d: ", place);
    if (counter != 0){
        for(j = 0; j < counter; j++){
            //printf("%d ", num[counter]);
        }
    }
    printf("\n");
}

 