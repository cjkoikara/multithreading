#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
struct input{
    int *row1;
    int *col2;
    int size;
};
void *findElem(struct input *vector){
    int i = 0;
    int j = 0;
    int *res=(int*)malloc(sizeof(int));
    for(int i =0;i<vector->size;i++)
    {
       //printf("row1[%d]=%d\n",i, vector->row1[i]);   
       //printf("col2[%d]=%d\n",i, vector->col2[i+3*j]);   
       *res += vector->row1[i]*vector->col2[i+3*j]; 

    }
    printf("%d\n",*res);
    return (void*)res;
}
int main()
{
    int size = 3; // number of rows in second matrix
    int i =0;
    int j = 0;
    int index=4; // number of cols in first matrix
    int arr1[3][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12}};
    int arr2[4][3]={{1,2,3},{4,5,6},{7,8,9},{10,11,12}};
    pthread_t tid[size*size];
    struct input vector[size*size];

    for(int i = 0;i<size;i++)
    {   
        for(int j =0;j<size;j++)
        {
            //printf("Creating thread\n");
            vector[i*size + j].row1=arr1[i];
            vector[i*size+j].size=index;
            vector[i*size+j].col2=&arr2[0][j];
            pthread_create(&tid[i*size + j],NULL,findElem,&vector[i*size + j]);
        }
    }
    sleep(3);
   int resarray[size][size]; 
   int *elem;
    for(int i =0;i<size;i++)
    {   
        for(int j =0;j<size;j++)
        {
            pthread_join(tid[i*size + j],&elem);
            printf("%d\t",*elem);
        }
        printf("\n");
    }
}