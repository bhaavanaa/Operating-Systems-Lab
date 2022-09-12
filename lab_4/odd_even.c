#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int max=20, f;
	f=fork();
	if(f>0)
	{
		printf("parent process-even series generation:\n");
		for(int i=0; i<=max; i++)	
		{
			if(i%2==0)
				printf("%d ", i);
		}
		printf("\n");
	}
	else if(f==0)
	{
		printf("child process-odd series generation:\n");
		for(int i=0; i<=max; i++)	
		{
			if(i%2!=0)
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
