#include "main.h"
/**
 * str_ncmp - compares two strings
 * @str1: the first string
 * @str2: the second string
 * @n: the index
 * Return: 0 on success, -1 on error
*/
int str_ncmp(char *str1, char *str2, int n)
{
	int i = 0;

	while (i < n)
	{
	if (str1[i] != str2[i])
		return (-1);
	i++;
	}
	return (0);
}
/**
 * retrieveBuiltIn - retrieves built-in commands
 * @str: command string
 * Return: 0
 */
int retrieveBuiltIn(char *str)
{
	int i = -1;

	if (str_len(str) == 4 && str_ncmp(str, "exit", 4) == 0)
		i = 0;
	else if (str_len(str) == 3 && str_ncmp(str, "env", 3) == 0)
		i = 1;
	return (i);
}

