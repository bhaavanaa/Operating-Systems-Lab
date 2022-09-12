#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int a[10]={2, 1, 5, 8, 6, 3, 4, 9, 7, 0};
	int b[10];
	for(int i=0; i<10; i++)
	{
		b[i]=a[i];
	}
	int f;
	f=fork();
	if(f>0)
	{
		printf("parent process-ascending order:\n");
		for(int i=0; i<10-1; i++)	
		{
			for(int j=0; j<10-i-1; j++)
			{
				if (a[j]>a[j+1])
				{ 
					int s=a[j];
					a[j]=a[j+1];
					a[j+1]=s;  
				}
			}
		}
		for(int i=0; i<10; i++)
			printf("%d ", a[i]);
		printf("\n");
	}
	else if(f==0)
	{
		printf("child process-descending order:\n");
		for(int i=0; i<10-1; i++)	
		{
			for(int j=0; j<10-i-1; j++)
			{
				if (b[j]<b[j+1])
				{ 
					int s=b[j];
					b[j]=b[j+1];
					b[j+1]=s;  
				}
			}
		}
		for(int i=0; i<10; i++)
			printf("%d ", b[i]);
		printf("\n");
	}
	else
	{
		printf("failed fork\n");
	}
	return(0);
}
