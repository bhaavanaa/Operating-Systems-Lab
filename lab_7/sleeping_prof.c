#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>
#include<sys/ipc.h>
#include<semaphore.h>


#define N 10


time_t end_time; //end time
sem_t mutex, students, prof; //Three semaphores 
int count=0; //The number of students waiting for doubts


void IdleProf();
void ArrivingStudent();


int main()
{
	pthread_t id1, id2[10];
	int status=0;
	end_time=time(NULL)+20; //end time

	//Semaphore initialization
	sem_init(&mutex, 0, 1);
	sem_init(&students, 0, 0);
	sem_init(&prof, 0, 1);

	//IdleProf_thread initialization
	status=pthread_create(&id1, NULL, (void *)IdleProf, NULL);
	if(status!=0)
		printf("creation of IdleProf thread failed!\n");
		
	//ArrivingStudent_thread initialization
	for(int i=0; i<10; i++)
	{
	    status=pthread_create(&id2[i], NULL, (void *)ArrivingStudent, NULL);
	    if(status!=0)
		    printf("creation of ArrivingStudent thread failed!\n");
    }
    
	/*ArrivingStudent_thread first blocked*/
	for(int i=0; i<10; i++)
	{
	    pthread_join(id2[i], NULL);
	}
	pthread_join(id1, NULL);
	return(0);
}


//IdleProf definition
void IdleProf() 
{
	while(time(NULL)<end_time || count>0)
	{
		sem_wait(&students); //wait(students)            
		sem_wait(&mutex); //wait(mutex)
		count--;
		printf("Prof: cleared doubt, count is:%d\n",count);
		sleep(1);     
		sem_post(&mutex); //post(mutex)
		sem_post(&prof); //post(prof)  
	}
}


//ArrivingStudent definition
void ArrivingStudent(void *arg) 
{
	while(1)
	{
		sem_wait(&mutex); //wait(mutex)
		if(count<10)
		{
			count++;
			printf("Student: add count, count is:%d\n",count);
			sem_post(&mutex); //post(mutex)
			sem_post(&students); //post(students)
			sem_wait(&prof); //wait(prof)
			//sleep(1);
		}
	}
}
