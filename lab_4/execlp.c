#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

#define bs 500

int main()
{
	int fd[2];
	char rm[500];
	int nb;
    pipe(fd);
    int f=fork();
	if(f>0)
	{
		wait(NULL);
		close(fd[1]);
		while(nb=read(fd[0],rm,bs)>0);
		printf("parent process: %s\n",rm);
		printf("\n");
	}
	else if(f==0)
	{
		printf("child process:\n");
        dup2(fd[1],1);
		execlp("ls", "ls", NULL);		
		printf("\n");
	}
	else
	{
		printf("failed fork\n");
	}
	return(0);
}
