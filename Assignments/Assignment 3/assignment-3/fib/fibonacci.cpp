#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<semaphore.h>

bool even;
int n;
int k=0;
int *fib;
sem_t seme;

void * print(void * v)
{
	printf("\nMy Thread ID is %u and my Process ID is %u\n",pthread_self(),getpid());
	printf("\nFib number: %d\n",*(int *)v);
}

void sube(int a, bool type)
{
	if(a%2==0 && type==true)
	{
			sem_wait(&seme);
			
			pthread_t t1;
			pthread_create(&t1,NULL,print,&a);
			pthread_join(t1,NULL);
			fib[k++]=a;
	}
}

void subo(int a, int b, bool type)
{
	if(a%2==1 && type==false)
	{
			pthread_t t1;
			pthread_create(&t1,NULL,print,&a);
			pthread_join(t1,NULL);
			fib[k++]=a;
			
			if(b%2!=0)
			sem_post(&seme);
	}
}

void * fiba()
{
	printf("\nMy Thread ID is %u and my Process ID is %u\n",pthread_self(),getpid());
	bool type=false;
	if(even)
	{
		printf("\nI am Even Process\n");
		type=true;
	}
	
	else
	{
		printf("\nI am Odd Process\n");
		type=false;
		even=true;
	}
	
	int a=1,b=2;
	
	while(a<n)
	{
		if(a%2==0)
		{
			
			sube(a,type);
		}
		
		if(a%2==1)
		{
			subo(a,b,type);
		}
			
		int t=a;
		a=b;
		b+=t;			
	}
	
	pthread_exit(0);
}

int main(int argc, char * argv[])
{
	pthread_t t1, t2;
	printf("\nMy Thread ID is %u and my Process ID is %u\n",pthread_self(),getpid());
	
	sem_init(&seme, 0, 1);
	even=false;
	
	printf("\nPlease Enter Data:	");
	scanf("%d",&n);
	fib=malloc(n * sizeof(int));
	fib[0]=1;
	fib[1]=2;
	
	pthread_create(&t1,NULL,fiba,&n);
	pthread_create(&t2,NULL,fiba,&n);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	for(int i=0;i<k;i++)
		printf("%d ",fib[i]);
		
	printf("\nProgram Exiting.\n");
}