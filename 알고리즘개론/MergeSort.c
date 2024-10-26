#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int op = 0;
void printarray(int A[], int length){
	for (int i = 0; i < length; i++)
	{
		printf("%d ", A[i]);
	}
	printf("\n");
}

int *mergesort(int A[], int length)
{
	int *result = (int *)calloc(length, sizeof(int));

	if (length == 1)
	{
		result[0] = A[0];
		return result;
	}
	else
	{
		int mid = length / 2;

		int *a = mergesort(A, mid);
		int *b = mergesort(A + mid, length - mid);

		int al = 0, bl = 0;
		for (int i = 0; i < length; i++)
		{
			if (al < mid && bl < length - mid)
			{
				if (a[al] > b[bl])
				{
					result[i] = a[al];
					al++;
				}
				else
				{
					result[i] = b[bl];
					bl++;
				}
			}
			else
			{
				if (al < mid)
				{
					result[i] = a[al];
					al++;
				}
				else
				{
					result[i] = b[bl];
					bl++;
				}
			}
			op++;
		}

		free(a);
		free(b);
	}

	return result;
}

int main(){
	// Merge sort
	printf("Merge sort\n");
	int* A = calloc(100, sizeof(int));

	// First test
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		int dup = 0;
		int randn;
		do
		{
			dup = 0;
			randn = rand() % 1000;
			for (int j = 0; j < i; j++)
			{
				if (A[j] == randn)
				{
					dup = 1;
					break;
				}
			}
			if (!dup)
				A[i] = randn;
		} while (dup);
	}
	printf("Case 1: \n");
	printf("Before Sorting: \n\n");
	printarray(A, 100);
	int index=0;
	int* result = mergesort(A, 100);
	printf("After Sorting: \n");
	printarray(result, 100);
	printf("operations : %d \n\n", op);
	free(result);

	// Second test
	op = 0;
	for (int j = 0; j < 100; j++)
	{
		A[j] = j + 1;
	}
	A[0] = 2;
	A[1] = 1;
	A[2] = 4;
	A[3] = 5;
	A[4] = 3;
	printf("Case 2: \n");
	printf("Before Sorting: \n\n");
	printarray(A, 100);
	index = 0;
	result = mergesort(A, 100);
	printf("After Sorting: \n");
	printarray(result, 100);
	printf("operations : %d \n\n", op);
	free(result);

	// Third test
	op = 0;
	for (int j = 0; j < 100; j++)
	{
		A[j] = 100 - j;
	}
	A[0] = 100 - 1;
	A[1] = 100 - 0;
	A[2] = 100 - 3;
	A[3] = 100 - 4;
	A[4] = 100 - 2;
	printf("Case 3: \n");
	printf("Before Sorting: \n\n");
	printarray(A, 100);
	index = 0;
	result = mergesort(A, 100);
	printf("After Sorting: \n");
	printarray(result, 100);
	printf("operations : %d \n", op);
	free(result);

	return 0;
}