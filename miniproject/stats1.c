//command line arguments and in C and integer inputs and conversion in the function and stdev, var in same function

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>


int n;

void * Mean(void ** param1);
void * Median(void ** param2);
void * Mode(void ** param3);
void * Range(void ** param4);
void * Median_low(void ** param5);
void * Median_high(void ** param6);
void * Quartiles(void ** param7);
void * Var_stdev(void ** param8);
void * Geometric_mean(void ** param9);
void * Harmonic_mean(void ** param10);


int main(int argc, char** argv)
{
    n=argc-1;

    pthread_t tid[10];
    pthread_attr_t attr;
    pthread_attr_init(&attr);

    void * mean1;
    void * median1;
    void * mode1;
    void * range1;
    void * median_low1;
    void * median_high1;
    void * quartiles1;
    void * var_stdev1;
    void * geometric_mean1;
    void * harmonic_mean1;

    pthread_create(&tid[0], &attr, Mean, argv);
    pthread_create(&tid[1], &attr, Median, argv);
    pthread_create(&tid[2], &attr, Mode, argv);
    pthread_create(&tid[3], &attr, Range, argv);
    pthread_create(&tid[4], &attr, Median_low, argv);
    pthread_create(&tid[5], &attr, Median_high, argv);
    pthread_create(&tid[6], &attr, Quartiles, argv);
    pthread_create(&tid[7], &attr, Var_stdev, argv);
    pthread_create(&tid[8], &attr, Geometric_mean, argv);
    pthread_create(&tid[9], &attr, Harmonic_mean, argv);

    pthread_join(tid[0], mean1);
    pthread_join(tid[1], median1);
    pthread_join(tid[2], mode1);
    pthread_join(tid[3], range1);
    pthread_join(tid[4], median_low1);
    pthread_join(tid[5], median_high1);
    pthread_join(tid[6], quartiles1);
    pthread_join(tid[7], var_stdev1);
    pthread_join(tid[8], geometric_mean1);
    pthread_join(tid[9], harmonic_mean1);

    return(0);
}


void *Mean(void ** param1)           
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
    pthread_exit(mean);
}


void *Median(void ** param2)            
{
    int a[n];
    float median;
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
        median=(float)(a[n/2-1]+a[n/2])/2;
    }
    else
    {
        median=a[n/2];
    }
    pthread_exit(median);
}


void *Mode(void ** param3)             
{
    int a[n];
    int count[n];
    int mode;
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


void *Range(void ** param4)             
{
    int a[n];
    int range;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param4[i+1]);
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
    range=a[n-1]-a[0];
    pthread_exit(range);
}


void *Median_low(void ** param5)       
{
    int a[n];
    int median_low;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param5[i+1]);
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
        median_low=a[n/2-1];
    }
    else
    {
        median_low=a[n/2];
    }
    pthread_exit(median_low);
}


void *Median_high(void ** param6)        
{
    int a[n];
    int median_high;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param6[i+1]);
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
    median_high=a[n/2];
    pthread_exit(median_high);
}


void *Quartiles(void ** param7)             
{
    int a[n];
    float q1, q3;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param7[i+1]);
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
    int n1=n/2;
    if(n1%2==0)
    {
        q1=(float)(a[n/4-1]+a[n/4])/2;
        q3=(float)(a[3*n/4-1]+a[3*n/4])/2;
    }
    else
    {
        q1=a[n/4];
        q3=a[3*n/4];
    }
    int ret[]={q1, q3};
    pthread_exit(ret);
}


void *Var_stdev(void ** param8)           
{
    int a[n];
    int sum=0;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param8[i+1]);
    }
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
    float ret1[]={variance, stdev};
    pthread_exit(ret1);
}


void *Geometric_mean(void ** param9)           
{
    int a[n];
    int prod=1;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param9[i+1]);
    }
    for(int i=0; i<n; i++)
    {
        prod=prod*a[i];
    }
    float gm=pow(prod, 1.0/n);
    pthread_exit(gm);
}


void *Harmonic_mean(void ** param10)           
{
    int a[n];
    float sum=0;
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(param10[i+1]);
    }
    for(int i=0; i<n; i++)
    {
        sum=sum+((float)1/a[i]);
    }
    float hm=(float)n/sum;
    pthread_exit(hm);
}
