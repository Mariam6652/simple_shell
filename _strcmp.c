#include "shell.h"
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
