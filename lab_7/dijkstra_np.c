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

void * process();
 


int main()
{
    pthread_t tid[10];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int i=0; i<10; i++)
    pthread_create(&tid[i], &attr, process, &i);
    for(int i=0; i<10; i++)
    pthread_join(tid[i], NULL);
    return(0);
}


void * process(void *q)
{
    int*p=q;
    int p1=*p;
    printf("pid=%d\n", p1);
    int done;
    item=0;
    do
    {
        buf[in]=item;
        item=item+5;
        in=(in+1)%BS;
        done=0;
        interested[p1]=1;
        while(1)
        {
            while(1)
            {
                if(k==p1)
                    break;
                if(interested[k]==0)
                    k=p1;
            }
            passed[p1]=1;
            done=1;
            for(int j=0; j<10; j++)
            {
                if(j!=p1)
                {
                    if(passed[p1]==1)
                    {
                        passed[j]=0;
                        done=0;
                    }
                    if(done==1)
                        break;
                }
            }
        }
        counter++;
        printf("producer counter=%d\n", counter);
        sleep(1);
        passed[p1]=0;
        interested[p1]=0;
    }while(1);
    pthread_exit(0);
}
