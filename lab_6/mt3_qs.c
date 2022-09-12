#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int a[100], n;

void * quicksort(int *p);
int partition(int beg, int end);

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
    quicksort(p);
    printf("the sorted array is\n");
    for(int i=0; i<n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
    pthread_exit(0);
    return(0);
}

int partition(int beg, int end)
{
	int t, u;
	int i=beg;
	int j=end;
	int pivot=a[beg];
	while(i<j)
	{
		while(a[i]<=pivot && i<end)
		{
			i++;
		}
		while(a[j]>pivot && j>beg)
		{
			j--;
		}
		if(i<j)
		{
			t=a[i];
			a[i]=a[j];
			a[j]=t;
		}
	}
	if(a[beg]>a[j])
	{
		u=a[beg];
		a[beg]=a[j];
		a[j]=u;
	}
	return (j);
}

void * quicksort(int *p)
{
    int beg=p[0];
    int end=p[1];
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
	if(beg<end)
	{
		int j=partition(beg, end);
        int p1[2]={beg, j-1};
        int p2[2]={j+1, end};
        pthread_create(&tid[0], &attr, quicksort, p1);
        pthread_create(&tid[1], &attr, quicksort, p2);
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
	}
}
