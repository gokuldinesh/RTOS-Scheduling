#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
int pc=0;

//Both taken from traSH shell's code
int external(char **, int);//executes process
char **split(char *);//splits to tokens
int the_code(int, char **);

int external(char **args, int pipes=1) 
{
    if(!active&&strcmp(arg[0],"entry")!=0)
	{
		printf("Command line interpretter not started\n");
		return 1;
	}
	else if(arg[0] == NULL)
		return 1;
	else if(strcmp(arg[0],"changedir")==0)
		return changedir(arg);
	else if(strcmp(arg[0],"exit")==0)
		return ext(arg);
	else if(strcmp(arg[0],"entry")==0)
		return entry(arg);
	else if(strcmp(arg[0],"log")==0)
		return log(arg);
	else
		return do_command(arg, pc);
}

int do_command(char **args, int pipes) 
{
	printf("pipe count = %d\n",pipes);
	// The number of commands to run
	const int commands = pipes + 1;
    int i = 0;

    int pipefds[2*pipes];

    for(i = 0; i < pipes; i++)
	{
        if(pipe(pipefds + i*2) < 0) 
		{
            perror("Couldn't Pipe");
            exit(EXIT_FAILURE);
        }
    }

    int pid;
    int status;

    int j = 0;
    int k = 0;
    int s = 1;
    int place;
    int commandStarts[10];
    commandStarts[0] = 0;

    // set all pipes to NULL, creates an array of where the next command starts
    while (args[k] != NULL)
	{
        if(!strcmp(args[k], "|"))
		{
            args[k] = NULL;
            // printf("args[%d] is now NULL", k);
            commandStarts[s] = k+1;
            s++;
        }
		/*else
		{
			pipes++
		}*/
        k++;
    }



    for (i = 0; i < commands; ++i) 
	{
        // place is where in args the program should
        // start running when it gets to the execution
        // command
        place = commandStarts[i];

        pid = fork();
        if(pid == 0) 
		{
            //if not last command
            if(i < pipes)
			{
                if(dup2(pipefds[j + 1], 1) < 0)
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            //if not first command&& j!= 2*pipes
            if(j != 0 )
			{
                if(dup2(pipefds[j-2], 0) < 0)
				{
                    perror("dup2");
                    exit(EXIT_FAILURE);
                }
            }

            int q;
            for(q = 0; q < 2*pipes; q++)
			{
                    close(pipefds[q]);
            }       
            if( execvp(args[place], args+place) < 0 )
			{
                    perror(*args);
                    exit(EXIT_FAILURE);
            }
        }
        else if(pid < 0)
		{
            perror("error");
            exit(EXIT_FAILURE);
        }

        j+=2;
    }

    for(i = 0; i < 2 * pipes; i++)
	{
        close(pipefds[i]);
    }

    for(i = 0; i < pipes + 1; i++)
	{
        wait(&status);
    }
}

char **split(char *input)
{
	int bsz = 128;
	pc=0;
	int pos=0;
	char *token;
	char **tokens = malloc(bsz * sizeof(char*));
	if(!tokens)
	{
		fprintf(stderr, "malloc fail\n");
		exit(-1);
	}
	token=strtok(input,"\t \n\0");//defined in string.h, used to split string into tokens
	while (token != NULL)
	{
		tokens[pos] = token;
		pos++;
		token=strtok(NULL, "\t \n\0");
	}
	tokens[pos] = NULL;
	return tokens;
}

int the_code(int argc, char **argv)
{
	char **arg;
	int ret;
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	for(int i=1;i<argc;i++)
	{
		fp = fopen(argv[i], "r");
		while ((read = getline(&line, &len, fp)) != -1)
		{
			arg=split(line);
			ret=external(arg);
			printf("\n");
		}
	}
	free(line);
	free(arg);
}