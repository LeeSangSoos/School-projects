#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct thread_data {
	int tid;
	int result;
};

int row;
int col;
int colnums[10000];

void *thread_mvm(void *arg)
{
	int nums[col];
	for (int i = 0; i < col; i++) {
		nums[i] = rand() % 10;
		printf("[ %d ]", nums[i]);
	}
	printf("\n");
	struct thread_data* t = (struct thread_data *) arg;

	int result=0;
	for (int i = 0; i < col; i++) {
		result += nums[i] * colnums[i];
	}
	t->result = result;
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("Usage: %s <row> <column>\n", argv[0]);
		exit(1);
	}

	row = atoi(argv[1]);
	col = atoi(argv[2]);

	pthread_t tid[row];
	struct thread_data t_data[row];

	srand(time(NULL));

	for (int i = 0; i < col; i++) {
		colnums[i] = rand() % 10;
	}

	printf(" *** Matrix *** \n");
	for (int i = 0; i < row; i++) {
		t_data[i].tid = i;
		if (pthread_create(&tid[i], NULL, thread_mvm, (void*)&t_data[i])) {
			printf("ERROR: pthread creation failed.n");
			exit(1);
		}
		pthread_join(tid[i], NULL);
	}

	printf(" *** Vector *** \n");
	for (int i = 0; i < col; i++) {
		printf("[ %d ]\n", colnums[i]);
	}
	printf("\n");

	printf(" *** Result *** \n");
	for (int i = 0; i < row; i++) {
		printf("[ %d ]\n", t_data[i].result);
	}

	
	return 0;
}
