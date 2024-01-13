#include "main.h"
/**
 * str_len - determines the length of string
 * @str: pointer pointing to a string
 * Return: length of string
*/
int str_len(char *str)
{
	int len = 0;

	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}
/**
 * getArgumentCount - counts arguments from
 * the command line
 * @line: command line
 * Return: number of arguments
 */
int getArgumentCount(char *line)
{
	int i = 0, search_space = 1, num_args = 0;

	while (line[i] != '\0')
	{
		if (line[i] != ' ' && search_space == 1)
		{
			num_args++;
			search_space = 0;
		}
		if (line[i + 1] == ' ')
			search_space = 1;
		i++;
	}
	return (num_args);
}

/**
 * str_dup - duplicates a string to another
 * @str: the string
 * Return: buffer
 */
char *str_dup(char *str)
{
	int len = 0, j = 0;
	char *buff;

	if (!str)
		return (NULL);
	while (str[len] != '\0')
		len++;
	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	while (str[j] != '\0')
	{
		buff[j] = str[j];
		j++;
	}
	buff[j] = '\0';
	return (buff);
}

/**
 * str_cpy - copies a string to another
 * @src: The source string
 * @dest: The destination string
 * Return: On success, the destination string
*/
char *str_cpy(char *dest, char *src)
{
	int l = 0, i;

	while (src[l] != '\0')
		l++;
	for (i = 0; i <= l; i++)
		dest[i] = src[i];
	return (dest);
}

/**
 * str_cat - concat a string to another
 * @dest: The destination string
 * @src: The source string
 * Return: On success, the resulting string
 */
char *str_cat(char *dest, char *src)
{
	int i = 0;

	while (*dest != '\0')
	{
		dest++;
		i++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		i++;
		src++;
	}
	*dest = '\0';
	dest -= i;
	return (dest);
}
