#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

#define BS 5
#define N 6

int counter;
int buf[BS];
int in=0, out=0;
int item;
int waiting[6]={0, 0, 0, 0, 0, 0};
int key, lock;

void * producer(int param);
void * consumer(int param);          
int test_set(int * target);


int main()
{
    pthread_t tid[6];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    lock=0;
    pthread_create(&tid[0], &attr, producer, 0);
    pthread_create(&tid[1], &attr, consumer, 1);
    pthread_create(&tid[2], &attr, producer, 2);
    pthread_create(&tid[3], &attr, consumer, 3);
    pthread_create(&tid[4], &attr, producer, 4);
    pthread_create(&tid[5], &attr, consumer, 5);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);
    pthread_join(tid[3], NULL);
    pthread_join(tid[4], NULL);
    pthread_join(tid[5], NULL);
    return(0);
}


int test_set(int * target)
{
    int rv=*target;
    *target=1;
    return(rv);
}


void * producer(int param)
{
    int p=param;
    item=0;
    do
    {
        while(counter==BS);
        buf[in]=item;
        item=item+5;
        in=(in+1)%BS;
        waiting[p]=1;
        key=1;
        while(waiting[p]==1 && key==1)
        {
            key=test_set(&lock);
        }
        counter++;
        printf("producer=%d, counter=%d\n", p, counter);
        waiting[p]=0;
        int j=(p+1)%N;
        while(waiting[j]!=1 && j!=p)
        {
            j=(j+1)%N;
        }
        if(j==p)
            lock=0;
        else
            waiting[j]=0;
    }while(1);
    pthread_exit(0);
}


void * consumer(int param)
{   
    int p=param;
    int i=0;
    do
    {
        i++;
        while(counter==0);
        item=buf[out];
        out=(out+1)%BS;
        waiting[p]=1;
        key=1;
        while(waiting[p]==1 && key==1)
        {
            key=test_set(&lock);
        }
        counter--;
        printf("consumer=%d, counter=%d\n", p, counter);
        waiting[p]=0;
        int j=(p+1)%N;
        while(waiting[j]!=1 && j!=p)
        {
            j=(j+1)%N;
        }
        if(j==p)
            lock=0;
        else
            waiting[j]=0;
    }while(1);
    pthread_exit(0);
}
