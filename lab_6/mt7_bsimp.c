#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<pthread.h>

int n, a[100], x, mark[100];
void *bs(void * param);

void main(int argc, char** argv)
{
	n=argc-1;
    int s;
	for(int i=0; i<n; i++)
	{
		a[i]=atoi(argv[i+1]);
        mark[i]=0;
	}
    printf("enter the number to be searched: ");
    scanf("%d", &x);
    int ret0;
    void * ret1;
    void * ret2;
    void * ret3;
    void * ret4;
    pthread_t tid[4];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if(n<4)
    {
        int p0[2]={0, n-1};
        pthread_create(&tid[0], &attr, bs, p0);
        pthread_join(tid[0], &ret0);
        if(ret0==1)
        {
            printf("element is present\n");
            printf("the indices are: ");
            for(int i=0; i<n; i++)
            {
                if(mark[i]==1)
                {
                    printf("%d ", i);
                }
            }
            printf("\n");
        }
        else
        {
            printf("the element is not present\n");
        }
    }
    else
    {
        int p1[2]={0, n/4};
        int p2[2]={n/4+1, n/2};
        int p3[2]={n/2+1, 3*n/4};
        int p4[2]={3*n/4+1, n-1};
        pthread_create(&tid[0], NULL, bs, p1);
        pthread_create(&tid[1], NULL, bs, p2);
        pthread_create(&tid[2], NULL, bs, p3);
        pthread_create(&tid[3], NULL, bs, p4);
        pthread_join(tid[0], &ret1);
        pthread_join(tid[1], &ret2);
        pthread_join(tid[2], &ret3);
        pthread_join(tid[3], &ret4);
        if(ret1==1 || ret2==1 || ret3==1 || ret4==1)
        {
            printf("the element is present\n");
            printf("the indices are: ");
            for(int i=0; i<n; i++)
            {
                if(mark[i]==1)
                {
                    printf("%d ", i);
                }
            }
            printf("\n");
        }
        else
        {
            printf("the element is not present\n");
        }
    }
    return(0);
}

void *bs(void * param)
{
    int *pa=(int*)param;
    int beg=pa[0];
	int end=pa[1];
	int flag=0;
	while(beg<=end)
	{
		int mid=(beg+end)/2;
		if(x==a[mid])
		{
			flag=1;
            mark[mid]=1;
            for(int i=mid+1; i<n; i++)
            {
                if(a[i]==x)
                {
                    mark[i]=1;
                }
                else if(a[i]>x)
                    break;
            }
            for(int i=mid-1; i>=beg; i--)
            {
                if(a[i]==x)
                {
                    mark[i]=1;
                }
                else if(a[i]<x)
                    break;
            }
			break;
		}
		else if(x<a[mid])
		{
			end=mid-1;
		}
		else
		{
			beg=mid+1;
		}
	}
	pthread_exit(flag);
}
