//in C++ and integer inputs and initial operations in main

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>

using namespace std;

int n;
int a[100];

void * Mean(void * param1);
void * Median(void * param2);
void * Mode(void * param3);
void * Range(void * param4);
void * Median_low(void * param5);
void * Median_high(void * param6);
void * Quartiles(void * param7);
void * Variance(void * param8);
void * Stdev(void * param9);
void * Geometric_mean(void * param10);
void * Harmonic_mean(void * param11);


int main()
{
    printf("enter the number of elements in the array: ");
    scanf("%d", &n);
    printf("enter the elements:\n");
    for(int i=0; i<n; i++)
    {
        scanf("%d", &a[i]);
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

    pthread_t tid[11];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    void * mean1;
    void * median1;
    void * mode1;
    void * range1;
    void * median_low1;
    void * median_high1;
    void * quartiles1;
    void * variance1;
    void * stdev1;
    void * geometric_mean1;
    void * harmonic_mean1;

    pthread_create(&tid[0], &attr, Mean, NULL);
    pthread_create(&tid[1], &attr, Median, NULL);
    pthread_create(&tid[2], &attr, Mode, NULL);
    pthread_create(&tid[3], &attr, Range, NULL);
    pthread_create(&tid[4], &attr, Median_low, NULL);
    pthread_create(&tid[5], &attr, Median_high, NULL);
    pthread_create(&tid[6], &attr, Quartiles, NULL);
    pthread_create(&tid[7], &attr, Variance, NULL);
    pthread_create(&tid[8], &attr, Stdev, NULL);
    pthread_create(&tid[9], &attr, Geometric_mean, NULL);
    pthread_create(&tid[10], &attr, Harmonic_mean, NULL);

    pthread_join(tid[0], mean1);
    pthread_join(tid[1], median1);
    pthread_join(tid[2], mode1);
    pthread_join(tid[3], range1);
    pthread_join(tid[4], median_low1);
    pthread_join(tid[5], median_high1);
    pthread_join(tid[6], quartiles1);
    pthread_join(tid[7], variance1);
    pthread_join(tid[8], stdev1);
    pthread_join(tid[9], geometric_mean1);
    pthread_join(tid[10], harmonic_mean1);

    return(0);
}


void *Mean(void * param1)           
{
    int sum=0;
    for(int i=0; i<n; i++)
    {
        sum=sum+a[i];
    }
    float mean=(float)sum/n;
    pthread_exit(mean);
}


void *Median(void * param2)            
{
    float median;
    if(n%2==0)
    {
        median=(float)(a[n/2-1]+a[n/2])/2;
    }
    else
    {
        median=a[n/2];
    }
    pthread_exit(median);
}


void *Mode(void * param3)             
{
    int count[n];
    int mode;
    for(int i=0; i<n; i++)
    {
        count[i]=0;
    }
    int x=a[0];
    int xi=0;
    for(int i=0; i<n; i++)  
    {
        if(a[i]==x)
        {
            count[xi]++;
        }
        else
        {
            x=a[i];
            xi=i;
            count[xi]++;
        }
    }
    int max=0;
    for(int i=0; i<n; i++)
    {
        if(count[i]>max)
        {
            max=count[i];
        }
    }
    for(int i=0; i<n; i++)
    {
        if(count[i]==max)
        {
            mode=a[i];
            break;
        }
    }
    pthread_exit(mode);
}


void *Range(void * param4)             
{
    int range;
    range=a[n-1]-a[0];
    pthread_exit(range);
}


void *Median_low(void * param5)       
{
    int median_low;
    if(n%2==0)
    {
        median_low=a[n/2-1];
    }
    else
    {
        median_low=a[n/2];
    }
    pthread_exit(median_low);
}


void *Median_high(void * param6)        
{
    int median_high;
    median_high=a[n/2];
    pthread_exit(median_high);
}


void *Quartiles(void * param7)             
{
    float q1, q3;
    int n1=n/2;
    if(n1%2==0)
    {
        q1=(float)(a[n/4-1]+a[n/4])/2;
        q3=(float)(a[3*n/4-1]+a[3*n/4])/2;
    }
    else
    {
        q1=a[n/4-1];
        q3=a[3*n/4-1];
    }
    int ret[]={q1, q3};
    pthread_exit(ret);
}


void *Variance(void * param8)           
{
    int sum=0;
    for(int i=0; i<n; i++)
    {
        sum=sum+a[i];
    }
    float mean=(float)sum/n;
    float sum1=0;
    for(int i=0; i<n; i++)
    {
        sum1=sum1+(mean-a[i])*(mean-a[i]);
    }
    float variance=sum1/n;
    pthread_exit(variance);
}


void *Stdev(void * param9)           
{
    int sum=0;
    for(int i=0; i<n; i++)
    {
        sum=sum+a[i];
    }
    float mean=(float)sum/n;
    float sum1=0;
    for(int i=0; i<n; i++)
    {
        sum1=sum1+(mean-a[i])*(mean-a[i]);
    }
    float variance=sum1/n;
    float stdev=sqrt(variance);
    pthread_exit(stdev);
}


void *Geometric_mean(void * param10)           
{
    int prod=1;
    for(int i=0; i<n; i++)
    {
        prod=prod*a[i];
    }
    float gm=pow(prod, 1.0/n);
    pthread_exit(gm);
}


void *Harmonic_mean(void * param11)           
{
    float sum=0;
    for(int i=0; i<n; i++)
    {
        sum=sum+((float)1/a[i]);
    }
    float hm=(float)n/sum;
    pthread_exit(hm);
}
