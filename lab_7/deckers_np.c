#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>

bool enter[10];
int turn;
int data=0;
void * process(void * arg)
{
	do
	{
	int i=(int)arg;
	enter[i]=true;
	{
		if(turn !=i)
		{
		   enter[i]=false;
		   while (turn !=i);    // busy wait
		  
		   enter[i]=true;
		}
	}

	// critical section
	if(i%2==0)
		data++;
	else
		data--;
	printf("CS %d data= %d \n ",i,data);
	sleep(1);
	turn=(i+1)%10;
	enter[i]=false;
	// remainder section
	}
	while(1);
}


int main()
{
	pthread_t tid[10];
	int i;

for(i=0;i<10;i++)
	pthread_create(&tid[i],NULL,process,i);

for(i=0;i<10;i++)
	pthread_join(tid[i],NULL);



return 0;
}


