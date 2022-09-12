#include <sys/time.h> 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#define BS 10

sem_t mutex,oxygenmutex,hydrogenmutex;
int atomcount = 0;
int moleculecount = 0;
int oxygencount = 0;
int hydrogencount = 0;


void *hydrogen(void * arg);
void *oxygen(void * arg);

int main()
{				
	pthread_t tid[20];	
	pthread_attr_t attr;	
	pthread_attr_init(&attr);	
	sem_post(&mutex);
	sem_post(&oxygenmutex);
	sem_post(&hydrogenmutex);
	for(int i=0;i<20;i=i+2)
	{
		pthread_create(&tid[i],&attr,hydrogen,NULL);
		pthread_create(&tid[i+1],&attr,oxygen,NULL);
		//pthread_create(&tid[i+2],&attr,hydrogen,NULL);
		
		
	}
	//printf("this is me\n");
	for(int i=0;i<20;i++)
	{	
		pthread_join(tid[i],NULL);
	}
	sem_destroy(&mutex);
	sem_destroy(&oxygenmutex);
	sem_destroy(&hydrogenmutex);
	return 0;
} 

void *hydrogen(void*arg)
{
		fflush(stdout); 
		printf("Hydrogen\n");
		sem_wait(&mutex);
		hydrogencount = hydrogencount + 1;
		//atomcount++;
		//while(atomcount==3)
		//	;
			
		if(oxygencount>=1 && hydrogencount>=2)
		{
			sem_post(&hydrogenmutex);
			hydrogencount = hydrogencount - 2;
			sem_post(&oxygenmutex);
			oxygencount = oxygencount - 1;
			printf("H One molecule created : H2O\n");
		}
		else
		{
			sem_post(&mutex);
		}
		//printf("I am here\n");
		sem_post(&hydrogenmutex);
				
	
	fflush(stdout); 
	pthread_exit(NULL);
	
}

void *oxygen(void*arg)
{
		fflush(stdout); 
		printf("Oxygen\n");
		sem_wait(&mutex);
		oxygencount = oxygencount + 1;
		//atomcount++;
		//while(atomcount==3)
		//	;
		if(hydrogencount>=2)
		{
			sem_post(&hydrogenmutex);
			hydrogencount = hydrogencount - 2;
			sem_post(&oxygenmutex);
			oxygencount = oxygencount - 1;
			printf("O One molecule created : H2O\n");
		}
		else
		{
			sem_post(&mutex);
		}
		sem_post(&oxygenmutex);
		sem_post(&mutex);
		
	fflush(stdout);
	pthread_exit(NULL);
	
}

