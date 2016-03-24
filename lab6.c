#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>


#define MAXLINE 80
#define MAXARG 20


void background(char * cmd) {
	int i = 0;
	char *argv[MAXARG];


	argv[i] = strtok(cmd,"\t \n");

	while(argv[i] != NULL) {
		i++;
		argv[i] = strtok(NULL, "\t \n");
	}

	int execReturn = execvp (argv[0], argv);
	exit(execReturn);
}

int main() {

	int childPid, childStatus;
	
	char exitString[] = "exit\n";
	char cmd[MAXLINE];

	for( ; ; )	
	{
		printf("mysh$ ");
		fgets(cmd, MAXLINE, stdin);		//read command from user

		// if the command in cmd is "exit\n", then terminate the program
		// otherwise, create a child process to handle that command.
		if(!strcmp(cmd, exitString)) {

			exit(0);

		}
		else {
			if((childPid = fork()) < 0) {
			
				perror("forK");
				exit(1);

			}
			else if (childPid == 0) {
		
				background(cmd);
				
			}

			//parent process waits until child terminates
			//fixes the propblem where the propt is re-printed before 
			//command output is displayed. 
			wait(&childStatus);
			
			
		}

	}


	return 0;
}