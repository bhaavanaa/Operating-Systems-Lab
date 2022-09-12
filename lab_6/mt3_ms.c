#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int a[100], n;

void merge(int beg, int end);
void *mergesort(int *p);

int main(int argc, char** argv)
{
    n=argc-1;
    int beg=0;
    int end=n-1;
    int p[2]={beg, end};
    for(int i=0; i<n; i++)
    {
        a[i]=atoi(argv[i+1]);
    }
    mergesort(p);
    printf("the sorted array is\n");
    for(int i=0; i<n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    pthread_exit(0);
    return(0);
}

void merge(int beg, int end)
{
	int mid=(beg+end)/2;
	int i=beg;
	int j=mid+1;
	int k;
	int b[n];
	for(k=beg; k<=end; k++)
	{
		if(i<=mid && j<=end)
		{
			if(a[i]<a[j])
			{
				b[k]=a[i];
				i++;
			}
			else
			{
				b[k]=a[j];
				j++;
			}
		}
		else
		{
			break;
		}
	}
	if(i>mid)
	{
		while(j<=end)
		{
			b[k]=a[j];
			j++;
			k++;
		}
	}
	else
	{
		while(i<=mid)
		{
			b[k]=a[i];
			i++;
			k++;
		}
	}
	for(int k=beg; k<=end; k++)
	{
		a[k]=b[k];
	}
}
	
void *mergesort(int *p)
{
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    int beg=p[0];
    int end=p[1];
	int mid;
	if(beg<end)
	{
		mid=(beg+end)/2;
        int p1[2]={beg, mid};
        int p2[2]={mid+1, end};
        pthread_create(&tid[0], &attr, mergesort, p1);
        pthread_create(&tid[1], &attr, mergesort, p2);
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
		merge(beg, end);
	}
}
