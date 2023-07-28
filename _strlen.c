#include "shell.h"
/**
 *  _strlen - function that returns the length of a string.
 * @s: string to calculate it's length
 * Return: the length of string
 */
int _strlen(char *s)
{
	int c = 0;
	char *p = s;

	while (*(p + c) != '\0')
	{
		c++;
	}
return (c);
}
