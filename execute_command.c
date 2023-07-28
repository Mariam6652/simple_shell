#include "shell.h"
/**
 * execute_command - Execute a command in a child process.
 * @command: The command to be executed.
 * @pname: the name of programe to display with error
 *
 * Return: nothing
 */
void execute_command(char *command, char *pname)
{
	pid_t pid;
	char *environ[] = { (char *) "PATH=/bin", 0}, *token, *argv[64];
	int status, wait_result, i = 0;	

	token = strtok(command, " ");
	if (token == NULL)
		return;
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		if (execve(argv[0], argv, environ) == -1)
		{
			perror(pname);
			exit(127);
		}
	}
	else
	{
		do
			wait_result = 	waitpid(pid, &status, 0);
		while (wait_result == -1 && errno == EINTR);

		if (wait_result == -1)
			exit(1);
		else
			exit(status >> 8);
	}
}
