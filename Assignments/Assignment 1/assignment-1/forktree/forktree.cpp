#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[])//implement arg verification
{
	int status,x;//x is loop control var for wait(), status stores return of child
	pid_t pid;
	int pidc;//return of fork
	
	//checking for arguments
	if(argc<3)
	{
		printf("\n Error: invalid arguments\n");
		return -1;
	}
	
	//input depth and children
	int children=atoi(argv[1]);
	int depth=atoi(argv[2]);
	
	pid_t id=getpid();
	printf("\nRoot: %d\n",id);
	
	while(depth>0)
	{
		int i;
		depth--;
		for(i=0;i<children;i++)
		{
			//sending child processes to wait
			pidc=fork();
			if(pidc==0)
					break;
		}
		
		//preventing parent function from making more children
		if(i==children)
			break;	
		printf("PID: %d, PPID: %d\n",getpid(),getppid());
	}
	if(pidc!=0)//lowest level of children have pidc=0
		for(x=0;x<children;x++)
		{
			pid =wait(&status);
			printf("Child with PID %d exited with status 0x%x\n",pid,status);
		}
	return 0;
}