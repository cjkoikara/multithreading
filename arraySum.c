/* 
This program uses multithreading to calculate the sum of the first N natural numbers.
Two threads are created to calculate the sum, one for even numbers and one for odd numbers.
The main thread will print the total sum.
*/

#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

/* Use structure to pass multiple arguments (and or return value from ) to the thread function */
struct args
{
    int oddoreven; // 0 for even, 1 for odd
    int size;
    void* base;
    
} args;

// thread function to calculate the sum of even or odd numbers
void *thread_fn(void * arg)
{
    void *result = calloc(1, sizeof(int));
    struct args *temp = (struct args*) arg;
    int index;

    // set the index for even or odd numbers
    if(temp->oddoreven)
    { 
       index = 1;
    }else{
       index = 0;
    }

   // loop through to calculate the sum
   int *array=(int*)(temp->base);
   for (;index<temp->size;index=index+2)
   {
    
    (*(int*)result)+=array[index];

   }
   return result;
}
int main()
{
    pthread_t thread_odd;
    pthread_t thread_even;
    
    int *result1=calloc(1,sizeof(int));
    int *result2=calloc(1, sizeof(int));

    int arr[] ={1,2,3,4,5,6,7,8,9,10};
    
    // allocate memory for the arguments
    struct args *oddarg = (struct args*)malloc(sizeof(struct args));
    
    oddarg->size = 10;
    oddarg->oddoreven = 1;
    oddarg->base = arr;

   struct args *evenarg = (struct args*)malloc(sizeof(struct args));  

    evenarg->size = 10;
    evenarg->oddoreven = 0;
    evenarg->base = arr;
   
    // create the threads
    pthread_create(&thread_odd, NULL, thread_fn,oddarg);
    pthread_create(&thread_even, NULL, thread_fn,evenarg);
    // wait for the threads to finish
    // join can receive the results
    pthread_join(thread_odd,(void**)&result1);
    pthread_join(thread_even,(void**)&result2);
    // print the total sum
    printf("%d\n", *result1 + *result2);

}