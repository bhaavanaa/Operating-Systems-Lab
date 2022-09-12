#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	printf("OS");
	fork();
	fork();
	fork();
	return(0);
}
