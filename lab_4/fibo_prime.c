#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int fib(int p)
{
	int f1=0,f2=1,fi=1;
	while(p>=1)
	{
		fi=f1+f2;
		f1=f2;
		f2=fi;
		p--;
	}
	return fi;
  }

int main()
{
	int n=50, sum=0;
	int f;
	f=fork();
	if(f>0)
	{
		printf("parent process-fibonacci series:\n");
		for(int i=0; i<=n; i++)
		{
			if(fib(i)<=n)
			{
				printf("%d ",fib(i));	
			}
			else
				break;
		}
		printf("\n");
	}
	else if(f==0)
	{
		printf("child process-prime number series:\n");
		for(int i=2; i<=n; i++)
		{
			int flag=0;
			for(int j=2; j<i; j++)
			{
				if(i%j==0)
				{
					flag=1;
				}
			}
			if(flag==0)
				printf("%d ", i);
		}
		printf("\n");
	}
	else
	{
		printf("failed fork\n");
	}
	return(0);
}
