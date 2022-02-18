#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

void sig_handler(int sig)
{
	printf("%d", sig);
	exit(0);
}

int main()
{
    char  inputLine[20];
    char* args_list[64];
    char* exitNow = "exit\n";
    char* quitNow = "quit\n";
    signal(SIGINT, sig_handler);
 
    while(!feof(stdin))
    {
    	printf("my-shell - > " );
    	//reading data from the user
        fgets(inputLine, 1024, stdin);
        
	if(inputLine[0]== '\n')
		continue;
	//handling exit conditions
	if(strcmp(inputLine, exitNow) == 0 || strcmp(inputLine, quitNow)==0 || inputLine[0]== '^')
	{
            exit(0);
	}

	int i = 0;
	
	//parsing user input
	char* input = inputLine;
	while(*input!= '\0')
	{
		while(*input == ' ' || *input == '\n'  ||*input =='\t' )
			*input++ = '\0';
		
		if(*input == '\0')
			break;

		args_list[i++] = input;
		
		while(*input!='\0' && *input!='\t' &&  *input!=' ' && *input!='\n')
			input++;

	}
	args_list[i++] = '\0';
	//end parsing
	
	//creating child process to perform exec
	int pid;
	int status;

	if((pid=fork())==0)
	{
		//check if command is cd
		if(strcmp(*args_list, "cd")==0)
		{
			//let parent handle cd
		}
		else
			execvp(*args_list, args_list);
		exit(0);
	}
	else
	{
		//parent process waiting for child process to terminate.
		while(wait(&status)!=pid)
		{
		}
	}
	
	//parent process handling cd
	if(strcmp(*args_list, "cd")==0)
        {
	        chdir(args_list[1]);
	}


    }

}
