#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int sum=0;

void *runner(void * param);

int main(int argc, char** argv)
{
    printf("the sum of numbers upto %s is\n", argv[1]);
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);
    printf("%d\n", sum);
    return(0);
}

void *runner(void * param)
{
    int p=atoi(param);
    for(int i=0; i<=p; i++)
    {   
        sum=sum+i;
    }
    pthread_exit(0);
}
