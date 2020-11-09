#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cmdline.h"

FILE *fptr;


/* void abrirFicheiro(const char *filename)
{

	if ((fptr = fopen(filename, "r")) == NULL)
	{
		printf("Erro ao abrir ficheiro!\n");
		// Program exits if file pointer returns NULL.
		exit(1);
	}

	return 0;
} */

/* void listarLinhasDoFicheiro()
{
	int MAX = 100;
	char c;
	c = fgetc(fptr);
	int linha = 1;
	char str[MAX];

	while (c != EOF) //ATENÇÂO
    { 
		
        printf ("%c", c); 
        c = fgetc(fptr); 
    } 

	while (fgets(str, MAX, fptr) != NULL)
	{
		printf("Linha %d: %s", linha, str);
		linha++;
	}
	if (!feof(fptr))
		printf("Erro de leitura\n");
}
 */

void read_command(char cmd[], char *par[])
{
	char line[1024];
	int count = 0, i = 0, j = 0;
	char *array[100], *pch;
	char s[2] = " ";

	//Read one line
	for (;;)
	{
		int c = fgetc(stdin);
		line[count++] = (char)c;
		

		if (c == '|' || c == '"' || c == '\39')
		{
			printf("[ERROR] Wrong request '%s'\n", cmd);
			exit(1);
		}
		if (c == '\n')
		{
			break;
		}
	}

	if (count == 1)
	{
		return;
	}

	pch = strtok(line, s); //line = "ls -a" 

	//parse the line into words
	while (pch != NULL)
	{
		array[i++] = strdup(pch);
		pch = strtok(NULL, s);
	}

	//first word is the command
	strcpy(cmd, array[0]);

	//other are parametrers
	for (j = 0; j < i; j++)
	{
		par[j] = array[j];
		
	}
	par[i] = NULL;

	
}

/* void argumentoHelp(void)
{
	printf("TEXTO-----------------------");
	terminarNanosheel();
} */

/* void terminarNanosheel(void)
{
} */

/* void executarComando(char **parsed)
{
	// Forking a child
	pid_t pid = fork();

	if (pid == -1)
	{
		printf("\nFailed forking child..");
		return;
	}
	else if (pid == 0)
	{
		if (execvp(parsed[0], parsed) < 0)
		{
			printf("\nCould not execute command..");
		}
		exit(0);
	}
	else
	{
		// waiting for child to terminate
		wait(NULL);
		return;
	}
}

const char *receberComandos(void)
{
	char comando[20];

	printf("nanoShell$ ");
	gets(comando);
	//scanf("%s", &comando);
	//printf("%s\n", &comando);
	//if (strcmp(comando,"bye"));

	//while (strcmp(comando, "bye"));

	//printf("[INFO] bye command detected. Terminating nanoShell\n");
	return comando;
} */

void type_prompt()
{
	static int first_time = 1;
	if (first_time)
	{ //clear screan
		const char *CLEAR_SCREEM_ANSI = "\e[1;1H\e[2J";
		write(STDOUT_FILENO, CLEAR_SCREEM_ANSI, 12);
		first_time = 0;
	}

	printf("nanoShell#"); //display prompt
}

int main(int argc, char **argv)
{

	char cmd[100], command[100], *parameters[20];
	// environment variable
	char *envp[] = {(char *)"PATH=/bin", 0};

	struct gengetopt_args_info args_info;
	if (cmdline_parser(argc, argv, &args_info) != 0)
	{
		exit(1);
	};

	/* if (args_info.file_given)
	{

		printf("-f / --ficheiro com o argumento : %s \n", args_info.file_arg);

		abrirFicheiro(args_info.file_arg);
		listarLinhasDoFicheiro(args_info.file_arg);
		fclose(fptr);
	}
 */
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
		exit(1);
	}

	while (1)
	{
		type_prompt();
		read_command(command, parameters);

		if (fork() != 0)
		{
			wait(NULL);
		}

		else if (strcmp(command, "bye") == 0)
		{
			break;
		}

		else
		{
			strcpy(cmd, "/bin/"); // "bin" + cmd eg cmd = /bin/
			strcat(cmd, command); // cmd + command eg cmd = /bin/ls

			execve(cmd, parameters, envp); // execute command  int execve(const char *pathname, char *const argv[],char *const envp[]);
		}
	}

	//const char *comandoPorExecutar = receberComandos();
	//printf(" DENTRO DO MAIN : %s", &comandoPorExecutar);
	//executarComando(comandoPorExecutar);
	/*printf("Hello World - %d", argc);
	for (int i = 0; i < argc; i++)
	{
		printf(" \n arg %d - %s\n", i, argv[i]);
	}

	if (!strcmp(argv[1],"-f") ){
		printf("\nAbrindo ficheiro...");


	}*/
}