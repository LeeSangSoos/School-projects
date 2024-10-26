#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define QSIZE 5
#define LOOP 30

typedef struct {
   int data[QSIZE];
   int put_index;
   int get_index;
   int count;
   pthread_mutex_t lock;
   pthread_cond_t notfull;
   pthread_cond_t notempty;
} queue_t;

void *produce (void *args);
void *consume (void *args);
void put_data (queue_t *q, int d);
void get_data (queue_t *q);

queue_t *qinit() 
{
   queue_t *q;

   q = (queue_t *) malloc(sizeof(queue_t));
   q->put_index = q->get_index = q->count = 0;
   pthread_mutex_init(&q->lock, NULL);
   pthread_cond_init(&q->notfull, NULL);
   pthread_cond_init(&q->notempty, NULL);

   return q;
}

void qdelete(queue_t *q) 
{
   pthread_mutex_destroy(&q->lock);
   pthread_cond_destroy(&q->notfull);
   pthread_cond_destroy(&q->notempty);
   free(q);
}

int main () 
{
   queue_t *q;
   pthread_t producer, consumer;

   q = qinit();

   pthread_create(&producer, NULL, produce, (void *)q);
   pthread_create(&consumer, NULL, consume, (void *)q);

   pthread_join (producer, NULL);
   pthread_join (consumer, NULL);
   
   qdelete(q);
}

void *produce(void *args) 
{
   int i, d;
   queue_t *q = (queue_t *)args;
   for (i = 0; i < LOOP; i++) {
      d = i;
      put_data(q, d);
   }
   pthread_exit(NULL);
}

void *consume(void *args) 
{
   int i;
   queue_t *q = (queue_t *)args;
   for (i = 0; i < LOOP; i++) {
      get_data(q);
   }
   pthread_exit(NULL);
}

void put_data(queue_t *q, int d) 
{
    pthread_mutex_lock(&(q->lock));

    if ((q->count) == 5) {
        pthread_cond_wait(&q->notfull, &q->lock);
    }
    
    q->data[5-q->count] = d;
    printf("put data %d to queue\n", q->data[5-q->count]);
    q->count++;

    pthread_cond_signal(&q->notempty);

    pthread_mutex_unlock(&(q->lock));
}
void get_data(queue_t *q) 
{
    pthread_mutex_lock(&(q->lock));

    if ((q->count) == 0) {
        pthread_cond_wait(&q->notempty, &q->lock);
    }

    q->count--;
    q->get_index = q->data[5-q->count];
    printf("got data %d from queue\n", q->get_index);
    

    pthread_cond_signal(&q->notfull);

    pthread_mutex_unlock(&(q->lock));
}

