

typedef struct
{
	int num;
	bool print_now;
}data;

bool status;

void *isPrime(void *data1)
{
	while(!status);
	int n = ((data *)data1)->num;
	
	int i;
	int *stat1 =(int *)malloc(sizeof(int));
	int temp = ((data *)data1)-> num;
	
	if (!(temp == 3 || temp == 5 || temp == 7 || temp == 2))
	{	
		for (i = 3; i <= sqrt(n); i += 2)
		{
			if (n % i == 0)
				pthread_exit((void *)stat1);
		}
	}
	
	while(!(((data *)data1)->print_now));
	
	printf("My Thread ID is %u and my process ID is %u\nPrime Number : %d\n",pthread_self(),getpid(),n);
	(((data *)data1)->print_now) = false;
	*stat1 = 2;
	pthread_exit((void *)stat1);
}

void *prime(void *num)
{
	printf("My Thread ID is %u and my process ID is %u\n",pthread_self(),getpid());
	int n = *(int *)num;
	
	int *result = malloc(sizeof(int) * (n / 2 + 1));
	int i=2;
	data data_arr[n / 2 + 1];
	
	pthread_t tid[n / 2 + 1];
	pthread_attr_t attr357 , attr;
	pthread_attr_init(&attr357);
	pthread_attr_setdetachstate(&attr357 , PTHREAD_CREATE_DETACHED);
	pthread_attr_init(&attr);
	
	data_arr[n / 2].num = 2;
	data_arr[n / 2].print_now = false;
	
	pthread_create((&tid[n / 2]),&attr357,isPrime,&data_arr[n / 2]);
	
	for (i = 3; i <= n; i+=2)
	{
		data_arr[(i / 2) - 1].num = i;
		data_arr[(i / 2) - 1].print_now = false;
		
		if(((i % 3)==0)||((i % 5)==0)||((i % 7)==0))
			{pthread_create((&tid[(i / 2) - 1]),&attr357,isPrime,&data_arr[(i / 2) - 1]);}
		else
			{pthread_create((&tid[(i / 2) - 1]),&attr,isPrime,&data_arr[(i / 2) - 1]);}
	}
	status = true;
	int *return_val;
	int j = 0;
	
	for (i = n; i >= 9; i-=2)
	{
		if(!(((i % 3)==0)||((i % 5)==0)||((i % 7)==0)))
		{
			data_arr[(i / 2) - 1].print_now = true;
			
			while(data_arr[(i / 2) - 1].print_now);
			pthread_join(tid[(i / 2) - 1],(void **)&return_val);
			
			return_val = (int *)return_val;
			
			if ((*return_val) == 2)
				result[j++] = i;
		}
	}
	
	for (i = 7; i >= 3; i-=2)
	{
		result[j++] = i;
		
		data_arr[(i / 2) - 1].print_now = true;
		
		while(data_arr[(i / 2) - 1].print_now);
	}
	
	data_arr[n / 2].print_now = true;
	
	while(data_arr[n / 2].print_now);
	
	result[j++] = 2;
	result[j] = -1;
	
	pthread_exit(result);
}

int parent(int argc, char **argv)
{
	int *result;
	int n,i = 0;
	
	pthread_t tid;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
	printf("My Thread ID is %u and my process ID is %u\n",pthread_self(),getpid());
	printf("Please enter the data: ");
	scanf(" %u",&n);
	n=(n%2==0)?(n-1):n;
	
	pthread_create(&tid,&attr,prime,&n);
	pthread_join(tid,(void *)&result);
	
	printf("From the Main Thread \n");
	while(result[i] != -1)
			printf(" %d ",result[i++]);
		
	printf("\nProgram exiting\n");
	return 0;
}