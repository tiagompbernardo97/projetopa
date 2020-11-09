#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "cmdline.h"

#define PRMTSIZ 255
#define MAXARGS 63
#define EXIT_COMMAND "bye"

/* const char* prompt()
{
	// prompt
	printf("nanoShell$");
	fgets(input, PRMTSIZ, stdin);
	return input;
} */
int normal_use()
{
jump:
	for (;;)
	{

		char input[PRMTSIZ + 1] = {0x0};
		char *ptr = input;
		char *args[MAXARGS + 1] = {NULL};
		int wstatus;

		printf("nanoShell$");
		fgets(input, PRMTSIZ, stdin);

		// ignore empty input
		if (*ptr == '\n')
			continue;

		// convert input line to list of arguments
		for (int i = 0; i < sizeof(args) && *ptr; ptr++)
		{
			if (*ptr == '|' || *ptr == '"' || *ptr == '\'')
			{
				printf("[ERROR] Wrong request '");
				for (int c = 0; c < sizeof(input); c++)
				{
					printf("%c", input[c]);
					
				}

				goto jump;//go back to the beginning
			}
			if (*ptr == ' ')
				continue;
			if (*ptr == '\n')
				break;

			for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++)
				;
			*ptr = '\0';
		}

		// built-in: exit
		if (strcmp(EXIT_COMMAND, args[0]) == 0)
		{
			printf("[INFO] bye command detected. Terminating nanoShell\n");
			return 0;
		}

		// fork child and execute program
		signal(SIGINT, SIG_DFL);
		if (fork() == 0)
			exit(execvp(args[0], args));
		signal(SIGINT, SIG_IGN);

		// wait for program to finish and print exit status
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			printf("<%d>", WEXITSTATUS(wstatus));
		}
	}
}

int normal_use_with_max_executions(int n_executions)
{
jump:
	for (int a = 1; a <= n_executions; a++)
	{

		char input[PRMTSIZ + 1] = {0x0};
		char *ptr = input;
		char *args[MAXARGS + 1] = {NULL};
		int wstatus;

		printf("Max number of executions: %d\n", n_executions);
		printf("%d / %d - ", a, n_executions);

		printf(" nanoShell$");
		fgets(input, PRMTSIZ, stdin);

		// ignore empty input
		if (*ptr == '\n')
			continue;

		// convert input line to list of arguments
		for (int i = 0; i < sizeof(args) && *ptr; ptr++)
		{
			if (*ptr == '|' || *ptr == '"' || *ptr == '\'')
			{
				printf("[ERROR] Wrong request ' ");
				for (int c = 0; c < sizeof(input); c++)
				{
					printf("%c '", input[c]);
				}

				goto jump;
			}
			if (*ptr == ' ')
				continue;
			if (*ptr == '\n')
				break;

			for (args[i++] = ptr; *ptr && *ptr != ' ' && *ptr != '\n'; ptr++)
				;
			*ptr = '\0';
		}

		// built-in: exit
		if (strcmp(EXIT_COMMAND, args[0]) == 0)
		{
			printf("[INFO] bye command detected. Terminating nanoShell\n");
			return 0;
		}

		// fork child and execute program
		signal(SIGINT, SIG_DFL);
		if (fork() == 0)
			exit(execvp(args[0], args));
		signal(SIGINT, SIG_IGN);

		// wait for program to finish and print exit status
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			printf("<%d>", WEXITSTATUS(wstatus));
		}
	}
}

int main(int argc, char **argv)
{
	struct gengetopt_args_info args_info;
	if (cmdline_parser(argc, argv, &args_info) != 0)
	{
		exit(1);
	};

	if (args_info.file_given)
	{

		printf("-f / --ficheiro com o argumento : %s \n", args_info.file_arg);

		abrirFicheiro(args_info.file_arg);
		listarLinhasDoFicheiro(args_info.file_arg);
		fclose(fptr);
	}
 
	if (args_info.help_given)
	{
		printf("NanoShell is a bash that can run:\n ");
		printf("-f --file <fileName> - Execute the command lines on the text file <fileName>, ignoring blank spaces and the character '#'.\n");
		printf("-h --help - Gives an explanation of how the ÑanoShell works.\n");
		printf("-m --max <int> - Gives the max number of command executions the NanoShell can run.\n");
		printf("-s --signalfile - Creates a signal.txt file with commands to have the possibility to send signals to NanoShell.\n");
		printf("NanoShell doesn't support the characters '|' or ' "
			   " '.\n");
		printf("Project designers: \n Nuno Ferreira - 2160856 \n Tiago Bernardo - 2160874 \n");
		return 0;
	}

	if (args_info.max_given)
	{
		//check if max given is a positive int
		printf("NUMBER OF TRIES: %d\n", args_info.max_arg);
		if (args_info.max_arg > 0)
		{
			
			normal_use_with_max_executions(args_info.max_arg);
			return 0;
		}
		else
			printf("You entered a negative number or zero\n.");
		return 0;
	}

	normal_use();
}