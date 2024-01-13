#include "shell.h"

/**
 * free_array - frees an array of strings
 * @arr: array of strings
 * Return: void
 */

void free_array(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
