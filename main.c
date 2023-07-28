#include "shell.h"
/**
 * main - Simple shell
 * @av : av is a NULL terminated array of strings.
 * @ac : ac is the number of items in av.
 * Return: Always 0.
 */

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int i, prompt = 1;

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
		if (_strcmp(line, "env") == 0)
		{
			i = 0;
			while (env[i] != NULL)
			{
				write(1, env[i], _strlen(env[i]));
				write(1, "\n", 1);
				i++;
			}
			continue;
		}
		if (ac >= 0 && line != NULL)
			execute_command(line, av[0]);

		free(line);
		line = NULL;
	}
	free(line);
	return (0);
}
