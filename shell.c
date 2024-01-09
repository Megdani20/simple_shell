#include "main.h"
/**
 * main - entry point
 * @argc: number of args
 * @argv: args
 * Return: 0
*/
int main(int argc __attribute__((unused)), char *argv[])
{
	size_t len;
	char *line = NULL, *command;
	int nr, loop = 0, status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "#soukaina/chaimaa$ ", 11);
		nr = getline(&line, &len, stdin);
		if (nr >= 0)
		{
			line[nr - 1] = '\0';
			command = removeWhitespace(line);
			if (!built_in(command, line, status))
				status = execfile(command, argv[0]);
			free(line);
			line = NULL;
		}
		else
		{
			free(line);
			break;
		}
		loop++;
	}
	return (0);
}

/**
 * removeWhitespace - ignores surrounded spaces
 * in the command line
 * @previous_line: command line
 * Return: command line after
 * spaces are removed
*/
char *removeWhitespace(char *previous_line)
{
	char *end_line, *new_line = previous_line;

	while (*new_line == ' ')
		new_line++;
	end_line = new_line + (str_len(new_line) - 1);
	while (end_line > new_line && *end_line == ' ')
		end_line--;
	*(end_line + 1) = '\0';
	return (new_line);
}
/**
 * createBuffer - allocates memory
 * for args
 * @num_args: number of args
 * @command: command line
 * Return: args
 */
char **createBuffer(int num_args, char *command)
{
	char **args, *delimeter = " ", *args_use;
	int i = 0;

	args = malloc((num_args + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	args_use = strtok(command, delimeter);
	while (args_use != NULL)
	{
	args[i] = str_dup(args_use);
	args_use = strtok(NULL, delimeter);
	i++;
	}
	args[i] = NULL;
	return (args);
}
/**
 * _free - free all memory
 * @args: arguments
 */
void _free(char **args)
{
	int i = 0;

	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
		free(args[i]);
		free(args);
	}
}
