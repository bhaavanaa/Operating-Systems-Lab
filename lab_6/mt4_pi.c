#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<time.h>
#include<pthread.h>

#define INTERVAL 1000

float x_2, y_2;

void * runner1(void * param);
void * runner2(void * param);

int main() 
{ 
	float origin_dist, pi; 
	int circle_points = 0, square_points = 0; 
    srand(time(NULL));
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr); 
    for (int i = 0; i < (INTERVAL * INTERVAL); i++) 
    { 
        pthread_create(&tid[0], &attr, runner1, NULL);
        pthread_create(&tid[1], &attr, runner2, NULL);
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
        origin_dist = x_2+y_2; 
        if (origin_dist <= 1) 
			circle_points++; 
        square_points++; 
        pi = (float)(4 * circle_points) / square_points; 
	} 
	printf("Final Estimation of Pi = %0.3f\n", pi); 
    return(0); 
}

void * runner1(void * param)
{
    float rand_x = (float)(rand() % (INTERVAL + 1)) / INTERVAL;
    x_2=((float)(rand_x*rand_x));
    pthread_exit(0);
} 

void * runner2(void * param)
{
    float rand_y = (float)(rand() % (INTERVAL + 1)) / INTERVAL;
    y_2=((float)(rand_y*rand_y));
    pthread_exit(0);
} 
