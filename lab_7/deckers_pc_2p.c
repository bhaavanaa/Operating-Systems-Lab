
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<pthread.h>

#define BS 5

int counter;
int buf[BS];
int in=0, out=0;
int item;
int turn=0;
int flag[2]={0, 0};

void * producer();
void * consumer();          


int main()
{
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid[0], &attr, producer, NULL);
    pthread_create(&tid[1], &attr, consumer, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    return(0);
}


void * producer()
{
    item=0;
    do
    {
        while(counter==BS);
        buf[in]=item;
        item=item+5;
        in=(in+1)%BS;
        flag[0]=1;
        while(flag[1]==1)
        {
            if(turn==1)
            {
                flag[0]=0;
                while(turn==1);
                flag[0]=1;
            }
        }
        counter++;
        printf("producer counter=%d\n", counter);
        flag[0]=0;
        turn=1;
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
        flag[0]=1;
        while(flag[0]==1)
        {
            if(turn==0)
            {
                flag[1]=0;
                while(turn==0);
                flag[1]=1;
            }
        }
        counter--;
        printf("consumer counter=%d\n", counter);
        flag[1]=0;
        turn=0;
    }while(1);
    pthread_exit(0);
}
