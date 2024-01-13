#include "shell.h"

/**
 * get__env - gets the environment variable
 * @_key: _key to get the value of
 * Return: value of the environment variable
 */

char *get__env(char *_key)
{
	char *value = NULL;
	int i = 0, j = 0, len__key = 0;

	if (_key == NULL)
		return (NULL);
	len__key = _strlen(_key);
	while (environ[i])
	{
		while (environ[i][j] == _key[j])
		{
			if (j == len__key - 1)
			{
				value = environ[i] + len__key + 1;
				return (value);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}

/**
 * echo_args - handles the $ builtin
 * @token: array of strings
 * @status: exit status
 */

void echo_args(char *token, int *status)
{
	char *value = NULL;
	(void)status;

	if (token == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return;
	}
	if (_strncmp(token, "$", 1) == 0)
	{
		value = get__env(token + 1);
		if (value != NULL)
		{
			write(STDOUT_FILENO, value, _strlen(value));
			write(STDOUT_FILENO, "\n", 1);
			return;
		}
	}
	if (_strncmp(token, "$$", 2) == 0)
	{
		value = _itoa(getpid());
		write(STDOUT_FILENO, value, _strlen(value));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	if (_strncmp(token, "$?", 2) == 0)
	{
		write(STDOUT_FILENO, get__env("?"), _strlen(get__env("?")));
		write(STDOUT_FILENO, "\n", 1);
		free(value);
		return;
	}
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * echo - handles the echo builtin with '"'
 * @token: array of strings
 * @status: exit status
 * Return: 1 if the command is a builtin, 0 if not
 */

int echo(char **token, int *status)
{
	int i = 1, flag = 0, j = 0;

	if (token == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (_strncmp(token[0], "echo", 4) != 0)
		return (0);
	if (token[1] == NULL)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	if (_strncmp(token[1], "$", 1) == 0 || _strncmp(token[1], "$$", 2) == 0 ||
	    _strncmp(token[1], "$?", 2) == 0)
	{
		echo_args(token[1], status);
		return (1);
	}
	for (i = 1; token[i] != NULL; i++)
	{
		for (j = 0; token[i][j] != '\0'; j++)
		{
			if (token[i][j] == '$')
			{
				flag = 1;
				echo_args(token[i] + j, status);
				break;
			}
			if (token[i][j] != '"')
				write(STDOUT_FILENO, &token[i][j], 1);
		}
		if (token[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
	}
	if (flag == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (1);
}
