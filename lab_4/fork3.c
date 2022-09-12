#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	printf("OS\n");
	fork();
	printf("course\n");
	fork();
	printf("2019\n");
	fork();
	printf("IIITDM\n");
	return(0);
}
