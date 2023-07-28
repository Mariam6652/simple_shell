#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

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
	char *environ[] = { (char *) "PATH=/bin", 0};
	char *token;
	char *argv[64];
	int i = 0;

	token = strtok(command, " ");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;
	pid = fork();
	if (pid == -1)
	{
		perror("Error");
		return;
	}
	if (pid == 0)
	{
		if (execve(command, argv, environ) == -1)
		{
			perror(pname);
			exit(127);
		}
	}
	else
	{
		wait(NULL);
	}
}
/**
 *  _strcmp - function that compares two strings.
 * @s1: the pointer to first string.
 * @s2: the pointer to second  string.
 * Return: diffrens between the strings
 */
int _strcmp(char *s1, char *s2)
{
	int d = 0;
	int c1 = 0;
	int c2 = 0;
	int s = 1;
	char *p1 = s1;
	char *p2 = s2;

	while (*(p1 + c1) != '\0')
	{
		c1++;
	}
	while (*(p2 + c2) != '\0')
	{
		c2++;
	}
	if (c2 > c1)
	{
		p1 = s2;
		p2 = s1;
		s = -1;
	}
	while (*p1 != '\0')
	{
		d = (int)*p1 - (int)*p2;
		p1++;
		p2++;
		if (d != 0)
		{
			return (d * s);
		}
	}
return (d * s);
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
	int prompt = 1;

	if (!isatty(STDIN_FILENO))
	{
		prompt = 0;
	}
	while (1)
	{
		if (prompt)
			write(1, "$ ", 2);

		read = getline(&line, &len, stdin);

		if (read == -1)
			break;
		else if (read == 1 && line[0] == '\n')
			continue;
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		if (_strcmp(line, "exit") == 0)
			break;
		if (ac >= 0 && line != NULL)
			execute_command(line, av[0]);

		free(line);
		line = NULL;
	}
	free(line);
	return (0);
}
