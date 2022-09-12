//not working well

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
int passed[6]={0, 0, 0, 0, 0, 0};
int interested[6]={0, 0, 0, 0, 0, 0};
int k=0;
int flag=1;

void * producer(int param);
void * consumer(int param);          


int main()
{
    pthread_t tid[6];
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
    int done;
    do
    {
        
    item=0;
        printf("herep\n");
        while(counter==BS);
        buf[in]=item;
        item=item+5;
        in=(in+1)%BS;
        while(flag==0);
        done=0;
        interested[p]=1;
        while(1)
        {
            while(1)
            {
                if(k==p)
                    break;
                if(interested[k]==0)
                    k=p;
            }
            flag=1;
            passed[p]=1;
            done=1;
            if(passed[p]==1)
            {
                passed[p]=0;
                done=0;
            }
            if(done==1)
                break;
        }
        counter++;
        printf("producer=%d, counter=%d\n", p, counter);
        passed[p]=0;
        interested[p]=0;
        flag=0;
    }while(1);
    pthread_exit(0);
}


void * consumer(int param)
{      
    do
    {
        printf("herec\n");
    int p=param;
    int done;
    int i=0; 
        i++;
        while(counter==0);
        item=buf[out];
        out=(out+1)%BS;
        while(flag==0);
        done=0;
        interested[p]=1;
        while(1)
        {
            while(1)
            {
                if(k==p)
                    break;
                if(interested[k]==0)
                    k=p;
            }
            flag=1;
            passed[p]=1;
            done=1;
            if(passed[p]!=1)
            {
                passed[p]=0;
                done=0;
            }
            if(done==1)
                break;
        }
        counter--;
        printf("consumer=%d, counter=%d\n", p, counter);
        passed[p]=0;
        interested[p]=0;
        //flag=0;
    }while(1);
    pthread_exit(0);
}
