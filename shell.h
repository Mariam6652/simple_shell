#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int _strlen(char *s);
int _strcmp(char *s1, char *s2);
void execute_command(char *command, char *pname, char **env);

#endif
