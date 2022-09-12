#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>

#define BS 5

int counter;
int buf[BS];
int in=0, out=0;
int item;
sem_t mutex;

void * producer();
void * consumer();          


int main()
{
    sem_init(&mutex, 0, 1);
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid[0], &attr, producer, NULL);
    pthread_create(&tid[1], &attr, consumer, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return(0);
}


void * producer(void * param)
{
    item=0;
    do
    {
        while(counter==BS);
        buf[in]=item;
        item=item+5;
        in=(in+1)%BS;
        sem_wait(&mutex);
        counter++;
        printf("producer counter=%d\n", counter);
        sem_post(&mutex);
    }while(1);
    pthread_exit(0);
}


void * consumer()
{   
    int i=0;
    do
    {
        i++;
        while(counter==0);
        item=buf[out];
        out=(out+1)%BS;
        sem_wait(&mutex);
        counter--;
        printf("consumer counter=%d\n", counter);
        sem_post(&mutex);
    }while(1);
    pthread_exit(0);
}
