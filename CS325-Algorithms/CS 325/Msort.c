/********************************************************************
 * This is for insertsort
 * this program reads the file data.txt and will sort
 * its contants 
 ******************************************************************/
#include <stdio.h> //standard c library 
#include <stdlib.h>




/* C program for Merge Sort */
#include <stdio.h>
#include <stdlib.h>

// Merges two sublistays of list[].
// First sublistay is list[l..m]
// Second sublistay is list[m+1..r]
void merge(int list[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp listays */
	int L[n1], R[n2];

	/* Copy data to temp listays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = list[l + i];
	for (j = 0; j < n2; j++)
		R[j] = list[m + 1 + j];

	/* Merge the temp listays back into list[l..r]*/
	i = 0; // Initial index of first sublistay
	j = 0; // Initial index of second sublistay
	k = l; // Initial index of merged sublistay
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			list[k] = L[i];
			i++;
		}
		else {
			list[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		list[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		list[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-listay of list to be sorted */
void mergeSort(int list[], int l, int r)
{
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(list, l, m);
		mergeSort(list, m + 1, r);

		merge(list, l, m, r);
	}
}

/* UTILITY FUNCTIONS */
/* Function to print an listay */
void printlistay(int A[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

/* Driver code */
int main()
{
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
    for(i = 0; i < 7; ++ i){                    
        //read number up until space 
        fscanf(data, "%d", &num_sort);
        // printf("\ngot lines: %d \n", num_sort);
        //setting up listay
        int *list = (int*)malloc(num_sort * sizeof(int));

        for(j = 0; j < num_sort; j++){ //loading in listay 
            fscanf(data, "%d", &k);
           // printf(" %d ", k);
            list[j] = k;
        }

        //sorting listay
        mergeSort(list, 0, num_sort - 1);
        printlistay(list, num_sort);

        for(j = 0; j < num_sort; j++){ //empty listay
            list[j] = 0;
        }
        free(list);

    }

    //closing file 
    fclose(data); 

    return 0;
}
