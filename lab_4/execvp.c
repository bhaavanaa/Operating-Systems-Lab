#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
	char *a[]={"ls", "-la", NULL};
	int f=fork();
	if(f>0)
	{
		wait(NULL);
		printf("parent process:\n");
		printf("\n");
	}
	else if(f==0)
	{
		printf("child process:\n");
		execvp(a[0], a);		
		printf("\n");
	}
	else
	{
		printf("failed fork\n");
	}
	return(0);
}
