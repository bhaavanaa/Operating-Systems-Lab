#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>
#include<semaphore.h>


int hydrogen=0, oxygen=0;
sem_t hydroqueue, oxyqueue, mutex;

void * hydrogenfn(void * param);
void * oxygenfn(void * param);


int main()
{
    sem_post(&mutex);
    sem_post(&hydroqueue);
    sem_post(&oxyqueue);
    pthread_t tid[20];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int i=0; i<20; i=i+2)
    {
        pthread_create(&tid[i], &attr, hydrogenfn, NULL);
        pthread_create(&tid[i+1], &attr, oxygenfn, NULL);
    }
    for(int i=0; i<20; i++)
    {
        pthread_join(tid[i], NULL);
    }
    sem_destroy(&mutex);
	sem_destroy(&oxyqueue);
	sem_destroy(&hydroqueue);
    return(0);
}


void * hydrogenfn(void * param)
{
    sem_wait(&mutex);
    hydrogen++;
    printf("hydrogen\n");
    if(hydrogen>=2 && oxygen>=1)
    {
        sem_post(&hydroqueue);
        //sem_post(&hydroqueue);
        hydrogen=hydrogen-2;
        sem_post(&oxyqueue);
        oxygen--;
        printf("H2O created\n");
    }
    else
        sem_post(&mutex);
    sem_post(&hydroqueue);
    pthread_exit(0);
}


void * oxygenfn(void * param)
{
    sem_wait(&mutex);
    oxygen++;
    printf("oxygen\n");
    if(hydrogen>=2)
    {
        sem_post(&hydroqueue);
        //sem_post(&hydroqueue);
        hydrogen=hydrogen-2;
        sem_post(&oxyqueue);
        oxygen=oxygen-1;
        printf("H2O created\n");
    }
    else
        sem_post(&mutex);
    sem_post(&oxyqueue);
    sem_post(&mutex);
    pthread_exit(0);
}

