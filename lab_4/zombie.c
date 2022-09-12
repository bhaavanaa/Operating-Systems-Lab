#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main() 
{ 
    int f = fork(); 
    if (f>0) 
        sleep(5); 
    else if(f==0)       
        exit(0); 
	else
		printf("failed fork\n");
  	return 0; 
} 
