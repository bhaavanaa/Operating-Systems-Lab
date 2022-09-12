#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
	int a[10]={2, 6, 5, 8, 1, 3, 4, 9, 7, 0};
	int b[5];
	for(int i=5; i<10; i++)
	{
		b[i-5]=a[i];
	}
	int f;
	f=vfork();
	if(f>0)
	{
		printf("parent process-leading ascending order:\n");
		for(int i=0; i<10-1; i++)	
		{
			for(int j=0; j<5-i-1; j++)
			{
				if (a[j]>a[j+1])
				{ 
					int s=a[j];
					a[j]=a[j+1];
					a[j+1]=s;  
				}
			}
		}
		for(int i=0; i<5; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
	else if(f==0)
	{
		printf("child process-remaining descending order:\n");
		for(int i=0; i<10-1; i++)	
		{
			for(int j=5; j<10-i-1; j++)
			{
				if (a[j]<a[j+1])
				{ 
					int t=a[j];
					a[j]=a[j+1];
					a[j+1]=t;  
				}
			}
		}
		for(int i=5; i<10; i++)
			printf("%d ", a[i]);
		printf("\n");
		exit(1);
	}
	else
	{
		printf("failed fork\n");
	}
	return(0);
}
