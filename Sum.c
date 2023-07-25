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
    int number; // the number of natural numbers to calculate
    int result; // the sum of the natural numbers
} args;

// thread function to calculate the sum of even or odd numbers
void *thread_fn(void * arg)
{
    struct args *temp = (struct args*) arg;
    int index;

    // set the index for even or odd numbers
    if(temp->oddoreven)
    { 
       index = 1;
    }else{
       index = 2;
    }

   // loop through to calculate the sum
   for (;index<=temp->number;index=index+2)
   {
    temp->result+=index;
   }

   return 0;
}
int main()
{
    pthread_t thread_odd;
    pthread_t thread_even;

    // allocate memory for the arguments
    struct args *oddarg = (struct args*)malloc(sizeof(struct args));

    oddarg->number = 10;
    oddarg->oddoreven = 1;
    oddarg->result = 0;

   struct args *evenarg = (struct args*)malloc(sizeof(struct args));  

    evenarg->number = 10;
    evenarg->oddoreven = 0;
    evenarg->result = 0;

    // create the threads
    pthread_create(&thread_odd, NULL, thread_fn,oddarg);
    pthread_create(&thread_even, NULL, thread_fn,evenarg);
    // wait for the threads to finish
    pthread_join(thread_odd,NULL);
    pthread_join(thread_even,NULL);
    // print the total sum
    printf("%d\n", oddarg->result + evenarg->result);
    free(oddarg);
    free(evenarg);
}