#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void printarray(int A[], int length){
	for(int i=0;i<length;i++){
		printf("%d ", A[i]);
	}
	printf("\n");
}

int bubblesort(int A[], int length){
	int index = 0;
	int op = 0;
	for(int i=1;i<length;i++){
		for(int j=i;j>0;j--){
			if(A[j] < A[j-1]){
				int temp = A[j];
				A[j] = A[j-1];
				A[j-1] = temp;
			}
			op++;
		}
		
	}
	return op;
}

int main(){
	//Bubble sort
	printf("Bubble sort\n");
	int A[100];
	//first test
	srand(time(NULL));
	for(int i=0;i<100;i++){
		int dup = 0;
		int randn;
		do{
			dup = 0;
			randn =rand()%1000;
			for(int j=0;j<i;j++){
				if(A[j] == randn){
					dup = 1;
					break;
				}
			}
			if(!dup) A[i] = randn;
		}while(dup);
	}
	printf("Case 1: \n");
	printf("Before Sorting: \n\n");
	printarray(A, 100);
	int op = bubblesort(A, 100);
	printf("After Sorting: \n");
	printarray(A, 100);
	printf("operations : %d \n", op);

	//Second test
	for(int i=0;i<100;i++){
		A[i] = i+1;
	}
	A[0] = 2;
	A[1] = 1;
	A[2] = 4;
	A[3] = 5;
	A[4] = 3;
	printf("Case 2: \n");
	printf("Before Sorting: \n\n");
	printarray(A, 100);
	op = bubblesort(A, 100);
	printf("After Sorting: \n");
	printarray(A, 100);
	printf("operations : %d \n", op);

	// Third test
	for (int i = 0; i < 100; i++)
	{
		A[i] = 100-i;
	}
	A[0] = 100-1;
	A[1] = 100-0;
	A[2] = 100-3;
	A[3] = 100-4;
	A[4] = 100-2;
	printf("Case 3: \n");
	printf("Before Sorting: \n\n");
	printarray(A, 100);
	op = bubblesort(A, 100);
	printf("After Sorting: \n");
	printarray(A, 100);
	printf("operations : %d \n", op);

	return 0;
}