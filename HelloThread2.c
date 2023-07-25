#include <stdio.h>
#include <pthread.h>

// Global variable
int i = 0;

// Mutex
pthread_mutex_t lock;

// Thread function
void* thread_func(void* arg)
{
    pthread_mutex_lock(&lock);
    for (int j = 0; j < 5; j++)
    {
        printf("Hello, Thread!\n");
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main()
{
    // Mutex initialization
    pthread_mutex_init(&lock, NULL);

    // Thread declarations
    pthread_t thread1, thread2;

    // Create threads
    pthread_create(&thread1, NULL, thread_func, NULL);
    pthread_create(&thread2, NULL, thread_func, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    return 0;
}