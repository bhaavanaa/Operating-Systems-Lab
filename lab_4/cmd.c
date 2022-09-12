#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>
#include<stdlib.h>

int main()
{
	int r=1;
	char com[100];
	char c[100][100];
	int t=0;
	while(r==1)
	{
		int f=vfork();
		if(f<0)
			printf("fork is not possible\n");
		else if(f>0)
		{
			wait(NULL);
		}
		else if(f==0)
		{
			printf("enter your command: ");
			scanf("%s", com);
			if(strcmp(com, "history")!=0)
			{
				for(int j=0; j<strlen(com); j++)
				{   
				    c[t][j]=com[j];        
				}
				t++;
				execlp(com,com, NULL);
			}
			else
			{
				for(int j=0; j<strlen(com); j++)
				{   
				    c[t][j]=com[j];        
				}
				t++;
				for(int i=0; i<t; i++)
				{
				    for(int g=0; g<strlen(c[i]); g++)
				    {
					    printf("%c",c[i][g]);
					}
					printf("\n");
				}
		    }
		    exit(0);
			
		}
		else
		{
			printf("failed fork\n");
		}
		//r='y';
		printf("Do you want to continue: ");
			scanf("%d", &r);
		
	}
	return(0);
}
