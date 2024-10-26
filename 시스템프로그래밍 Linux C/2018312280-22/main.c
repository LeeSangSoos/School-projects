#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
int point_total=0, point_circle=0;
int r=1000;

void *draw(void *args) {
	int x, y;
	int ptot = 0, pcir = 0;
	int pnum = (intptr_t) args;
	for (int i = 0; i < pnum; i++) {
		srand(time(NULL));
		x = rand()%(r+1);
		y = rand()%(r+1);
		ptot++;
		if (sqrt(pow(x,2)+pow(y,2))<=r) {
			pcir++;
		}
	}
	pthread_mutex_lock(&m);
	point_total += ptot;
	point_circle += pcir;
	pthread_mutex_unlock(&m);
}

void main(int argc, char* argv[]) {
	char* pos = NULL;
	int threadnum=strtol(argv[1], &pos,10);
	int pointnum=strtol(argv[2], &pos, 10);

	pthread_t thread[threadnum];
	for (int i = 0; i < threadnum; i++) {
		pthread_create(&thread[i], NULL, draw, (void*)(intptr_t)pointnum);
	}
	for (int i = 0; i < threadnum; i++) {
		pthread_join(thread[i], NULL);
	}
	float pi = 4 * ((float)point_circle) / ((float)point_total);
	printf("pi: %f\n", pi);
}