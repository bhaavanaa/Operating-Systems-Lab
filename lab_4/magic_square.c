#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
	int n;

	printf("enter the order of the magic square: ");
	scanf("%d", &n);
	int a[n][n];	    
	int f=vfork();

	if(f==0)
	{
		printf("child process-magic square generation:\n");
		for(int g=0; g<n; g++)
		{
			for(int h=0; h<n; h++)
			{
				a[g][h]=0;
			}
		}

		int i=n/2;
		int j=n-1;
		for(int h=1; h<=n*n; h++)
		{
			if(i==-1 && j==n)
			{
				i=0;
				j=n-2;
			}
			else
			{			
				if(i<0)
				{
					i=n-1;
				}		
				if(j==n)
				{
					j=0;
				}
			}
			if(a[i][j]!=0)
			{
				j=j-2;
				i=i+1;
			}
			a[i][j]=h;		
			i=i-1;
			j=j+1;
		}
		for(int g=0; g<n; g++)
		{
			for(int h=0; h<n; h++)
			{
				printf("%d ", a[g][h]);
			}
			printf("\n");
		}
		printf("\n");
		exit(1);
	}
	else if(f>0)
	{
	    wait(NULL);
		printf("parent process-magic square verification:\n");
		int sum=n*((n*n)+1)/2;
		int flag=0;
		for(int g=0; g<n; g++)
		{
			//printf("here\n");
			int t=0;
			for(int h=0; h<n; h++)
			{
				//printf("me\n");
				t=t+a[g][h];
				//printf("%d ", a[g][h]);
				//printf("%d\n", t);				
			}
			//printf("%d\n", t);
			if(t!=sum)
			{	
				flag=1;
				break;
			}
		}
		if(flag==0)
		{
			//printf("here1\n");
			for(int g=0; g<n; g++)
			{
				int t=0;
				for(int h=0; h<n; h++)
				{
					t=t+a[h][g];				
				}
				if(t!=sum)
				{
					flag=1;
					break;
				}
			}
		}
		if(flag==0)
		{
			//printf("here2\n");
			int t=0;
			for(int g=0; g<n; g++)
			{
				t=t+a[g][g];
			}
			if(t!=sum)
				flag=1;
		}
		if(flag==0)
		{
			//printf("here3\n");
			int p=0;
			int q=n-1;
			int sum1=0;
			for(int g=0; g<n; g++)
			{
				sum1=sum1+a[p][q];
				p=p+1;
				q=q-1;
			}
			if(sum1!=sum)
				flag=1;
		}
		if(flag==0)
			printf("magic square verified\n");
		else
			printf("wrong magic square\n");
	}
	else
	{
		printf("failed fork\n");
	}
	return(0);
}
