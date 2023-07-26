#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

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
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return;
	}
	if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror(pname);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - Simple shell
 * @av : av is a NULL terminated array of strings.
 * @ac : ac is the number of items in av.
 * Return: Always 0.
 */

int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		write(1, "$ ", 2);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			return (0);
		}
		else if (read == 1 && line[0] == '\n')
		{
			continue;
		}
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}

		if (ac >= 0 && line != NULL)
			execute_command(line, av[0]);
	}

	free(line);
	return (0);
}
