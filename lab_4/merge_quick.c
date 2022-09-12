#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int n;
int a[100];
int a1[100];


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
	

void mergesort(int beg, int end)
{
	int mid;
	if(beg<end)
	{
		mid=(beg+end)/2;
		int f=vfork();
		if(f>0)
			mergesort(beg, mid);
		else if(f==0)
		{
			mergesort(mid+1, end);
			exit(1);
		}
		merge(beg, end);
	}
}


/*int partition(int beg, int end)
{
	int t, u;
	int i=beg;
	int j=end;
	int pivot=a1[beg];
	while(i<j)
	{
		while(a1[i]<=pivot && i<end)
		{
			i++;
		}
		while(a1[j]>pivot && j>beg)
		{
			j--;
		}
		if(i<j)
		{
			t=a1[i];
			a1[i]=a1[j];
			a1[j]=t;
		}
	}
	if(a1[beg]>a1[j])
	{
		u=a1[beg];
		a1[beg]=a1[j];
		a1[j]=u;
	}
	return (j);
}


void quicksort(int beg, int end)
{
	if(beg<end)
	{
		int j=partition(beg, end);
		/*for(int b=beg; b<=end; b++)
		{
			cout<<a[b]<<" ";
		}
		cout<<"\n";
		quicksort(beg, j-1);
		quicksort(j+1, end);
	}
}*/


int main()
{
	printf("enter the number of elements to be sorted: ");
	scanf("%d", &n);

	printf("enter the elements to be sorted:\n");
	for(int h=0; h<n; h++)
	{
		scanf("%d", &a[h]);
	}
	int beg=0;
	int end=n-1;
	mergesort(beg, end);
	
	printf("the sorted array is:\n");
	for(int h=0; h<n; h++)
	{
		printf("%d ", a[h]);
	}
	printf("\n");
	return(0);
}
