#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

sem_t full;
sem_t empty;
pthread_mutex_t mutex;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % BUFFER_SIZE;
    count++;
}

int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % BUFFER_SIZE;
    count--;
    return tmp;
}

void *producer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        printf("produced%d\n",i);
        sleep(3);
        put(i);
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    int i;
    for (i = 0; i < BUFFER_SIZE; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int tmp = get();
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        printf("%d\n", tmp);
    }
}

int main() {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_mutex_init(&mutex, NULL);

    pthread_t producer_tid;
    pthread_t consumer_tid;

    pthread_create(&producer_tid, NULL, producer, NULL);
    pthread_create(&consumer_tid, NULL, consumer, NULL);

    pthread_join(producer_tid, NULL);
    pthread_join(consumer_tid, NULL);

    sem_destroy(&full);
    sem_destroy(&empty);
    pthread_mutex_destroy(&mutex);
}