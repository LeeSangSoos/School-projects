#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int add = 0;
int mul = 0;
void printmatrix(int **m, int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
}

int** standard(int **a, int **b, int n){
	add-=n*n;
	int **result = (int **)calloc(n, sizeof(int *));
	for(int i=0;i<n;i++){
		result[i] = (int *)calloc(n, sizeof(int));
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			result[i][j]=0;
			for(int k=0;k<n;k++){
				result[i][j]+=a[i][k]*b[k][j];
				add++;
				mul++;
			}
		}
	}

	return result;
}

int** divide_and_conquer(int **A, int **B, int n)
{
	
	int **result = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		result[i] = (int *)calloc(n, sizeof(int));
	}
	if(n==2){
		result[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
		result[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
		result[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
		result[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
		add+=4;
		mul+=8;
	}
	else{
		int **a = (int **)calloc(n/2, sizeof(int *));
		int **b = (int **)calloc(n / 2, sizeof(int *));
		int **c = (int **)calloc(n / 2, sizeof(int *));
		int **d = (int **)calloc(n / 2, sizeof(int *));
		int **e = (int **)calloc(n / 2, sizeof(int *));
		int **f = (int **)calloc(n / 2, sizeof(int *));
		int **g = (int **)calloc(n / 2, sizeof(int *));
		int **h = (int **)calloc(n / 2, sizeof(int *));
		for (int i = 0; i < n/2; i++)
		{
			a[i] = (int *)calloc(n/2, sizeof(int));
			b[i] = (int *)calloc(n / 2, sizeof(int));
			c[i] = (int *)calloc(n / 2, sizeof(int));
			d[i] = (int *)calloc(n / 2, sizeof(int));
			e[i] = (int *)calloc(n / 2, sizeof(int));
			f[i] = (int *)calloc(n / 2, sizeof(int));
			g[i] = (int *)calloc(n / 2, sizeof(int));
			h[i] = (int *)calloc(n / 2, sizeof(int));
		}
		
		
		//divide matrix
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				a[i][j] = A[i][j];
				e[i][j] = B[i][j];
			}
		}
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = n/2; j < n; j++)
			{
				b[i][j - n / 2] = A[i][j];
				f[i][j - n / 2] = B[i][j];
			}
		}
		for (int i = n / 2; i < n; i++)
		{
			for (int j = 0; j < n/2; j++)
			{
				c[i - n / 2][j] = A[i][j];
				g[i - n / 2][j] = B[i][j];
			}
		}
		for (int i = n / 2; i < n; i++)
		{
			for (int j = n/2; j < n; j++)
			{
				d[i - n / 2][j - n / 2] = A[i][j];
				h[i - n / 2][j - n / 2] = B[i][j];
			}
		}
		//divide matrix

		int **r = (int **)calloc(n / 2, sizeof(int *));
		int **s = (int **)calloc(n / 2, sizeof(int *));
		int **t = (int **)calloc(n / 2, sizeof(int *));
		int **u = (int **)calloc(n / 2, sizeof(int *));
		int **temp1 = (int **)calloc(n / 2, sizeof(int *));
		int **temp2 = (int **)calloc(n / 2, sizeof(int *));
		for (int i = 0; i < n/2; i++)
		{
			r[i] = (int *)calloc(n / 2, sizeof(int));
			s[i] = (int *)calloc(n / 2, sizeof(int));
			t[i] = (int *)calloc(n / 2, sizeof(int));
			u[i] = (int *)calloc(n / 2, sizeof(int));
			temp1[i] = (int *)calloc(n / 2, sizeof(int));
			temp2[i] = (int *)calloc(n / 2, sizeof(int));
		}

		// marge matrix
		temp1 = divide_and_conquer(a, e, n / 2);
		temp2 = divide_and_conquer(b, g, n / 2);
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				r[i][j] = temp1[i][j] + temp2[i][j];
				add++;
			}	
		}
		printf("sub matrix r size: %d x %d\n", n / 2, n / 2);
		printmatrix(r,n/2);
		temp1 = divide_and_conquer(a, f, n / 2);
		temp2 = divide_and_conquer(b, h, n / 2);
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = n / 2; j < n; j++)
			{
				s[i][j - n / 2] = temp1[i][j - n / 2] + temp2[i][j - n / 2];
				add++;
			}
		}
		printf("sub matrix s size: %d x %d\n", n / 2, n / 2);
		printmatrix(s, n / 2);
		temp1 = divide_and_conquer(c, e, n / 2);
		temp2 = divide_and_conquer(d, g, n / 2);
		for (int i = n / 2; i < n; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				t[i - n / 2][j] = temp1[i - n / 2][j] + temp2[i - n / 2][j];
				add++;
			}
		}
		printf("sub matrix t size: %d x %d\n", n / 2, n / 2);
		printmatrix(t, n / 2);
		temp1 = divide_and_conquer(c, f, n / 2);
		temp2 = divide_and_conquer(d, h, n / 2);
		for (int i = n / 2; i < n; i++)
		{
			for (int j = n / 2; j < n; j++)
			{
				u[i - n / 2][j - n / 2] = temp1[i - n / 2][j - n / 2] + temp2[i - n / 2][j - n / 2];
				add++;
			}
		}
		printf("sub matrix u size: %d x %d\n", n / 2, n / 2);
		printmatrix(u, n / 2);

		for (int i = 0; i < n / 2; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				result[i][j] = r[i][j];
			}
		}
		for (int i = 0; i < n / 2; i++)
		{
			for (int j = n / 2; j < n; j++)
			{
				result[i][j] = s[i][j-n/2];
			}
		}
		for (int i = n / 2; i < n; i++)
		{
			for (int j = 0; j < n / 2; j++)
			{
				result[i][j] = t[i - n/ 2][j];
			}
		}
		for (int i = n / 2; i < n; i++)
		{
			for (int j = n / 2; j < n; j++)
			{
				result[i][j] = u[i - n / 2][j - n / 2];
			}
		}
		// merge
		free(a);
		free(b);
		free(c);
		free(d);
		free(e);
		free(f);
		free(g);
		free(h);
		free(r);
		free(s);
		free(t);
		free(u);
		free(temp1);
		free(temp2);
	}

	return result;
}

int main(){
	int n = 4;
	printf("Matrix multiplication\n");
	int **A = (int **)calloc(n, sizeof(int *));
	int **B = (int **)calloc(n, sizeof(int *));
	int **C = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		A[i] = (int *)calloc(n, sizeof(int));
		B[i] = (int *)calloc(n, sizeof(int));
		C[i] = (int *)calloc(n, sizeof(int));
	}
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		for(int j= 0 ;j<n;j++){
			A[i][j] = rand() % 1000;
			B[i][j] = rand() % 1000;
		}
	}

	printf("Test 4x4: \n");
	printf("Maxtrix A : \n");
	printmatrix(A,n);
	printf("Maxtrix B : \n");
	printmatrix(B, n);
	add = 0;
	mul = 0;
	printf("standard method: \n");
	C = standard(A,B,n);
	printf("Result : \n");
	printmatrix(C, n);
	printf("Operations: addition : %d, multiplication : %d, total : %d \n", add, mul, add+mul);

	add = 0;
	mul = 0;
	printf("divide and conquer method: \n");
	C = divide_and_conquer(A, B, n);
	printf("Result : \n");
	printmatrix(C, n);
	printf("Operations: addition : %d, multiplication : %d, total : %d \n", add, mul, add + mul);

	free(A);
	free(B);
	free(C);

	n=8;
	A = (int **)calloc(n, sizeof(int *));
	B = (int **)calloc(n, sizeof(int *));
	C = (int **)calloc(n, sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		A[i] = (int *)calloc(n, sizeof(int));
		B[i] = (int *)calloc(n, sizeof(int));
		C[i] = (int *)calloc(n, sizeof(int));
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			A[i][j] = rand() % 1000;
			B[i][j] = rand() % 1000;
		}
	}

	printf("Test 8x8: \n");
	printf("Maxtrix A : \n");
	printmatrix(A, n);
	printf("Maxtrix B : \n");
	printmatrix(B, n);
	add = 0;
	mul = 0;
	printf("standard method: \n");
	C = standard(A, B, n);
	printf("Result : \n");
	printmatrix(C, n);
	printf("Operations: addition : %d, multiplication : %d, total : %d \n", add, mul, add + mul);

	add = 0;
	mul = 0;
	printf("divide and conquer method: \n");
	C = divide_and_conquer(A, B, n);
	printf("Result : \n");
	printmatrix(C, n);
	printf("Operations: addition : %d, multiplication : %d, total : %d \n", add, mul, add + mul);

	free(A);
	free(B);
	free(C);
	return 0;
}