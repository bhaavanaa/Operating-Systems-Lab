#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<stdbool.h>

void *runner1(void * param1);
void *runner2(void * param2);

int turn=0;
bool flag[2] = {false, false};
int x=5;

int main()
{
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid[0], &attr, runner1, NULL);
    pthread_create(&tid[1], &attr, runner2, NULL);
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);    
    return(0);
}

void *runner1(void * param1)
{
    do
    {
        flag[0] = true;
        turn = 1;
        while (flag[1] == true && turn == 1);
        x++;
        printf("process i: %d\n", x);
        fflush(stdout);
        flag[0] = false;
    }while(1);
    pthread_exit(0);
}

void *runner2(void * param2)
{
    do
    {
        flag[1] = true;
        turn = 0;
        while (flag[0] == true && turn == 0);
        x--;
        printf("process j: %d\n", x);
        fflush(stdout);
        flag[1] = false;
    }while(1);
    pthread_exit(0);
}
