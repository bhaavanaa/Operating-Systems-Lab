#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define M 3
#define K 2
#define N 3

int A[M][K]={{1, 2}, {3, 4}, {5, 6}};
int B[K][N]={{7, 8, 9}, {10, 11, 12}};
int C[M][N];

struct dt
{
    int i;
    int j;
};

void *runner(void * param);

int main(int argc, char** argv)
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    printf("the resultant matrix is:\n");
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            struct dt * data=(struct dt *) malloc(sizeof(struct dt));
            data->i=i;
            data->j=j;
            pthread_create(&tid, &attr, runner, data);
        }
    }
    pthread_join(tid, NULL);
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<N; j++)
        {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return(0);
}

void *runner(void * param)
{
    int sum=0;
    struct dt * data=param;
    for(int g=0; g<K; g++)
    {
        sum=sum+(A[data->i][g]*B[g][data->j]);
    }
    C[data->i][data->j]=sum;
    pthread_exit(0);
}
