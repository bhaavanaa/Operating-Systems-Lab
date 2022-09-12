#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	if(fork() && fork())
	{
		fork();
	}
	if(fork() || fork())
	{
		fork();
		fork();
	}
	printf("IIITDM\n");
	return(0);
}
