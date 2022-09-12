#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	for(int i=1; i<=2; i++)
    {
		fork();
	    printf("*");
    }
	return(0);
}
