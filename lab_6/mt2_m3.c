#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

int n;
void *runner1(void ** param1);
void *runner2(void ** param2);
void *runner3(void ** param3);

int main(int argc, char** argv)
{
    n=argc-1;
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner1, argv);
    pthread_create(&tid, &attr, runner2, argv);
    pthread_create(&tid, &attr, runner3, argv);
    pthread_join(tid, NULL);
    return(0);
}

void *runner1(void ** param1)
{
    int a[n];
    int sum=0;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param1[i+1]);
    }
    for(int i=0; i<n; i++)
    {
        sum=sum+a[i];
    }
    float mean=(float)sum/n;
    printf("mean= %0.2f\n", mean);
    pthread_exit(0);
}

void *runner2(void ** param2)
{
    int a[n];
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param2[i+1]);
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
    if(n%2==0)
    {
        printf("median= %0.2f\n", (float)(a[n/2-1]+a[n/2])/2);
    }
    else
    {
        printf("median= %d\n", a[n/2]);
    }
    pthread_exit(0);
}

void *runner3(void ** param3)
{
    int a[n];
    int count[n];
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param3[i+1]);
    }
    for(int i=0; i<n; i++)
    {
        count[i]=0;
    }
    for(int i=0; i<n; i++)  
    {
        for(int j=0; j<n; j++)
        {
            if(a[i]==a[j])
            {
                count[i]++;
                count[j]++;    
            }
        }
    }
    int max;
    for(int i=0; i<n; i++)
    {
        if(count[i]>max)
        {
            max=count[i];
        }
    }
    printf("mode= ");
    for(int i=0; i<n; i++)
    {
        if(count[i]==max)
        {
            printf("%d ", a[i]);
            break;
        }
    }
    printf("\n");
    pthread_exit(0);
}
