#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>

int a[100];

void *runner(void * param);

int main(int argc, char** argv)
{
    printf("the prime numbers upto %s are\n", argv[1]);
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    for(int k=2; k<=atoi(argv[1]); k++)
    {
        pthread_create(&tid, &attr, runner, k);
    }
    pthread_join(tid, NULL);
    printf("\n");
    return(0);
}

void *runner(void * param)
{
    int p=param;
    int flag=0;
    int count;
    
        if(p%i==0)
        {
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("%d ", p);
    }
    pthread_exit(0);
}
