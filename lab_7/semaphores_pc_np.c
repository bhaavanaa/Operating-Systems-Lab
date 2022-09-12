#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>

#define BS 5
#define N 6

int counter;
int buf[BS];
int in=0, out=0;
int item;
sem_t mutex;

void * producer(int param);
void * consumer(int param);          


int main()
{
    sem_init(&mutex, 0, 1);
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
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
        sem_wait(&mutex);
        counter++;
        printf("producer=%d, counter=%d\n", p, counter);
        sem_post(&mutex);
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
        sem_wait(&mutex);
        counter--;
        printf("consumer=%d, counter=%d\n", p, counter);
        sem_post(&mutex);
    }while(1);
    pthread_exit(0);
}
