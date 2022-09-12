#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main() 
{      
	int f=fork(); 
  
    if (f==0) 
        printf("Parent process\n"); 
    else if (f>0) 
    { 
		sleep(10); 
        printf("Child process"); 
    } 
	else
		printf("Failed fork\n");
    return 0; 
} 
