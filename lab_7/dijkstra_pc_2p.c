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
int passed[2]={0, 0};
int interested[2]={0, 0};
int k=0;

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
    int done;
    item=0;
    do
    {
        while(counter==BS);
        buf[in]=item;
        item=item+5;
        in=(in+1)%BS;
        done=0;
        interested[0]=1;
        while(1)
        {
            while(1)
            {
                if(k==0)
                    break;
                if(interested[k]==0)
                    k=0;
            }
            passed[0]=1;
            done=1;
            if(passed[1]==1)
            {
                passed[0]=0;
                done=0;
            }
            if(done==1)
                break;
        }
        counter++;
        printf("producer counter=%d\n", counter);
        passed[0]=0;
        interested[0]=0;
    }while(1);
    pthread_exit(0);
}


void * consumer()
{   
    int done;
    int i=0;    
    do
    {
        i++;
        while(counter==0);
        item=buf[out];
        out=(out+1)%BS;
        done=0;
        interested[1]=1;
        while(1)
        {
            while(1)
            {
                if(k==1)
                    break;
                if(interested[k]==0)
                    k=1;
            }
            passed[1]=1;
            done=1;
            if(passed[0]==1)
            {
                passed[1]=0;
                done=0;
            }
            if(done==1)
                break;
        }
        counter--;
        printf("consumer counter=%d\n", counter);
        passed[1]=0;
        interested[1]=0;
    }while(1);
    pthread_exit(0);
}
