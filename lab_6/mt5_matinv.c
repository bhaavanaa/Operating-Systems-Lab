#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int n;
int adj[100][100];
int a[100][100];

struct str
{
    int k;
    int *y;
};

void cofactor(int temp[n][n], int p, int q);
void * determinant(void * param);
void * adjoint(void * param1);

int main(int argc, char** argv)
{
    printf("myself\n");/*
    n=atoi(argv[1]);
    int c=2;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            a[i][j]=atoi(argv[c]);
            printf("m%d ", a[i][j]);
            c++;
        }
    }
    printf("tea");
    float ans[n][n];
    int det;
    struct str *s=(struct str*)malloc(sizeof(struct str));
    s->k=n;
    s->y=(int *)a;
    pthread_t tid[2];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    
    pthread_create(&tid[0], &attr, determinant, s);
    pthread_create(&tid[1], &attr, adjoint, a);
    pthread_join(tid[0], det);
    pthread_join(tid[1], NULL);
    printf("here\n");
    if(det==0)
    {
        printf("the matrix is singular, inverse doesnt exist\n");
    }
    else
    {
        printf("the inverse of the martix is:\n");
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                ans[i][j]=adj[i][j]/(float)det;
                printf("%0.2f ", ans[i][j]);
            }
            printf("\n");
        }
    }*/
    return(0);
}

void getCofactor(int A[n][n], int temp[n][n], int p, int q, int n) 
{ 
	int i=0, j=0; 
	
	for (int row=0; row<n; row++) 
	{ 
		for (int col=0; col<n; col++) 
		{ 
			if (row!=p && col!=q) 
			{ 
				temp[i][j++]=A[row][col];
				//printf("%d  ", A[row][col]); 
				if (j==n-1) 
				{ 
					j=0; 
					i++; 
				} 
			} 
		} 
	} 
}

void * determinant(void * param) 
{ 
    struct str *pa = param;    
    int n=pa->k;
    int *a=pa->y;
	int d=0;
	if (n==1)
    { 
		pthread_exit(*(a + 0*1)); 
    }
    int temp[n][n]; 
    int sign=1;
    pthread_t tid1;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    printf("hereme\n");
	for(int f=0; f<n; f++) 
	{
        int d1;
        printf("me\n");
        for(int g=0; g<n; g++)
	{
	    for(int h=0; h<n; h++)
	    {
	        printf("%d ", a[g][h]);
	    }
	    printf("\n");
	}
		getCofactor(a, temp, 0, f, n);
		struct str *t=(struct str*)malloc(sizeof(struct str));
		t->k=n-1;
        t->y=temp;
        pthread_create(&tid1, &attr, determinant, t); 
        pthread_join(tid1, d1);
        d = d + sign * (*(a + 0*n + f)) *d1;
		//d = d+ sign * a[0][f] * d1; 
		sign = -sign; 
	} 
	//printf("d=%d\n", d);
    pthread_exit(d);
} 

void * adjoint(void * param1) 
{ 
    int *a=param1;
	if(n==1) 
	{ 
		adj[0][0]=1; 
	} 
	int sign=1, temp[n][n];
    pthread_t tid2;
    pthread_attr_t attr;
    pthread_attr_init(&attr); 
	for (int i=0; i<n; i++) 
	{ 
		for (int j=0; j<n; j++) 
		{ 
			getCofactor(a, temp, i, j, n); 
			if((i+j)%2==0)
            {
                sign=1;
            } 
            else
            {
                sign=-1;
            }
            struct str *r=(struct str*)malloc(sizeof(struct str));
            r->k=n-1;
            r->y=temp;
            int d2;
            pthread_create(&tid2, &attr, determinant, r); 
            pthread_join(tid2, d2);
			adj[j][i] = (sign)*d2; 
		} 
	} 
    pthread_exit(0);
} 
