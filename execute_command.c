#include "shell.h"
/**
 * execute_command - Execute a command in a child process.
 * @command: The command to be executed.
 * @pname: the name of programe to display with error
 * @env : the envirenment varable
 * Return: nothing
 */
void execute_command(char *command, char *pname, char **env)
{
	pid_t pid;
	char *argv[64], *token;
	int status, i = 0;

	token = strtok(command, " ");
	if (token == NULL)
		return;
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	if (access(argv[0], X_OK) == -1)
	{
		perror(pname);
		return;
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (execve(argv[0], argv, env) == -1)
		{
			perror(pname);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}
