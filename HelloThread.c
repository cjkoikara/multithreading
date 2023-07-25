#include<pthread.h>
#include<stdio.h>
#include<unistd.h> 
pthread_mutex_t lock;

void * Hello(void* arg)
{
  pthread_mutex_lock(&lock); 
    printf("Hello ");
    sleep(1);
    pthread_mutex_unlock(&lock);
    return 0;
}
void * Thread(void* arg)
{
    pthread_mutex_lock(&lock);
    printf("Thread\n");
    sleep(2);
    pthread_mutex_unlock(&lock);
    return 0;
}
int main()
{

    pthread_t thread1, thread2;
    // Mutex initialization
    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1,NULL,Hello,NULL);
    pthread_create(&thread2,NULL,Thread,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
}

