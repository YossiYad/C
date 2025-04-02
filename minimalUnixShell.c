#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX 1024

int main()
{
	char input[MAX], tempInput[MAX];
	char* ptrInput = NULL,* allInput[MAX];
	pid_t pid;
	printf("\n################################################################################\n");
	printf("\t\t\t   welcome to my shell\n");
	printf("\t\t     To exit, type \"leave\" or \"Leave\"");
	printf("\n################################################################################\n");
	
	while (1)
	{
		printf("myShell> ");
		fgets(input, sizeof(input), stdin);
		input[strlen(input) - 1] = '\0';
		strcpy(tempInput, input);
		ptrInput = strtok(tempInput, " \t");
		
		if (strcmp(ptrInput, "leave") == 0 || strcmp(ptrInput, "Leave") == 0)
		{
			break;
		}
		
		else
		{
			int stat = 0;
			if((pid = fork()) == 0)
			{
				const char* path = getenv("PATH");
				int i = 0;
				char tempPath[strlen(path)],* strtokPtr = NULL;
				strcpy(tempPath, path);
				strtokPtr = strtok(input, " \t");
				while(strtokPtr)
				{
					allInput[i++] = strtokPtr;
					strtokPtr = strtok(NULL, " \t");
				}
				allInput[i] = NULL;
				strtokPtr = strtok(tempPath, ":");
				while(strtokPtr)
				{
					char wichFile[MAX];
					strcpy(wichFile, strtokPtr);
					strcat(wichFile, "/");
					strcat(wichFile, allInput[0]);
					execv(wichFile, allInput);
					strtokPtr = strtok(NULL, ":");
				}
				exit(1);
			}
			else
			{
				wait(&stat);
				if (stat != 0)
				{
					printf("INVALID COMMAND\n");
				}
			}
		}


	}

	return 0;
}
