#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int n, a[100];
void *smallest(void * param);
void *Q1(void * param);
void *median(void * param);
void *Q3(void * param);
void *largest(void * param);

int main(int argc, char** argv)
{
    n=argc-1;
    void * small;
    void * q1;
    int med;
    void * q3;
    void * large;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(argv[i+1]);
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(a[j]>a[j+1])
            {
                int s=a[j];
                a[j]=a[j+1];
                a[j+1]=s;
            }
        }
    }
    pthread_t tid[5];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid[0], &attr, smallest, NULL);
    pthread_create(&tid[1], &attr, Q1, NULL);
    pthread_create(&tid[2], &attr, median, NULL);
    pthread_create(&tid[3], &attr, Q3, NULL);
    pthread_create(&tid[4], &attr, largest, NULL);
    pthread_join(tid[0], &small);
    pthread_join(tid[1], &q1);
    pthread_join(tid[2], &med);
    pthread_join(tid[3], &q3);
    pthread_join(tid[4], &large);
    printf("the summary is: %d %d %d %d %d\n", small, q1, med, q3, large);
    return(0);
}

void * smallest(void * param)
{
    pthread_exit(a[0]);
}

void * largest(void * param)
{
    pthread_exit(a[n-1]);
}

void * median(void * param)
{
    if(n%2==0)
    {
        pthread_exit((a[n/2-1]+a[(n/2)])/2);
    }
    else
    {
        pthread_exit(a[n/2-1]);
    }
}

void * Q1(void * param)
{
    if((n/2)%2==0)
    {
        pthread_exit((a[n/4-1]+a[n/4])/2);
    }
    else
    {
        pthread_exit(a[n/4-1]);
    }
}

void * Q3(void * param)
{
    if((3*n/2)%2==0)
    {
        pthread_exit((a[3*n/4-1]+a[3*n/4])/2);
    }
    else
    {
        pthread_exit(a[3*n/4-1]);
    }
}
