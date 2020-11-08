#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cmdline.h"

FILE *fptr;

void abrirFicheiro(const char *filename)
{

	if ((fptr = fopen(filename, "r")) == NULL)
	{
		printf("Erro ao abrir ficheiro!\n");
		// Program exits if file pointer returns NULL.
		exit(1);
	}

	return 0;
}

void listarLinhasDoFicheiro()
{
	int MAX = 100;
	char c;
	c = fgetc(fptr);
	int linha = 1;
	char str[MAX];

	/*while (c != EOF) 
    { 
		
        printf ("%c", c); 
        c = fgetc(fptr); 
    } */

	while (fgets(str, MAX, fptr) != NULL)
	{
		printf("Linha %d: %s", linha, str);
		linha++;
	}
	if (!feof(fptr))
		printf("Erro de leitura\n");
}

void argumentoHelp(void)
{
	printf("TEXTO-----------------------");
	terminarNanosheel();
}

void terminarNanosheel(void)
{
}

void executarComando(char **parsed)
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
		printf("Lista de autores: \n Nuno Ferreira - 2160856 \n Tiago Bernardo - 2160874 \n");
	}

	const char *comandoPorExecutar = receberComandos();
	printf(" DENTRO DO MAIN : %s", &comandoPorExecutar);
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