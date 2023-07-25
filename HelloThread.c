#include<pthread.h>
#include<stdio.h>
#include<unistd.h> 
pthread_mutex_t lock;

void * threadFunc(void* arg)
{
  pthread_mutex_lock(&lock); 
    printf("%s ", (char*) arg);
    sleep(1);
    pthread_mutex_unlock(&lock);
    return 0;
}
int main()
{
    char* msg1 = "Hello";
    char* msg2 = "Thread\n";
    pthread_t thread1, thread2;
    // Mutex initialization
    pthread_mutex_init(&lock, NULL);

    pthread_create(&thread1,NULL,threadFunc,msg1);
    pthread_create(&thread2,NULL,threadFunc,msg2);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
}