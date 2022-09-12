#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	if(fork() || fork())
		fork();
	printf("OS2019\n");
	return(0);
}
