#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * execute_command - Execute a command in a child process.
 * @command: The command to be executed.
 *
 * Return: 0 if success or 1 if errer
 */
int execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	argv[0] = command;
	argv[1] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return (1);
	}
	else if (pid == 0)
	{
		if (execve(command, argv, NULL) == -1)
		{
			perror(command);
			return (1);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
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
		printf("$ ");
		fflush(stdout);

		read = getline(&line, &len, stdin);

		if (read == -1)
		{
			printf("\n");
			break;
		}
		else if (read == 1 && line[0] == '\n')
		{
			continue;
		}
		if (line[read - 1] == '\n')
		{
			line[read - 1] = '\0';
		}

		if (execute_command(line) > 0)
		{
			if (ac >= 0)
				perror(av[0]);
		}
	}

	free(line);
	return (0);
}
