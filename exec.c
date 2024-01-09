#include "main.h"
/**
 * execfile - executes the specified file
 * @command_line: the file to execute
 * @programName: the first argv of main
 * Return: the status of the last process
*/
int execfile(char *command_line, char *programName)
{
	pid_t pid;
	char **args = NULL, **env = environ, *path;
	int arg_num, stat = 0;

	if (*command_line != '\0' && *command_line != '#')
	{
		command_line = locateComment(command_line);
		arg_num = getArgumentCount(command_line);
		args = createBuffer(arg_num, command_line);
		path = full_path(args[0]);
		if (path != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execve(path, args, env);
				perror(args[0]);
			}
			else if (pid > 0)
				waitpid(pid, &stat, 0);
			else
				perror("fork");
		}
		else
		{
			write(STDERR_FILENO, programName, strlen(programName));
			write(STDERR_FILENO, ": 1: ", 5);
			write(STDERR_FILENO, args[0], strlen(args[0]));
			write(STDERR_FILENO, ": not found\n", 12);
		}
		if (path != args[0])
			free(path);
		_free(args);
	}
	return (stat);
}

/**
 * full_path - provides the full path of a file
 * @file: the file to look for
 * Return: pointer to the path of the file
*/
char *full_path(char *file)
{
	char path[BUFF_SIZE], *ptr_path, **env = environ, *paths, *f_paths;
	int i = 0;

	if (access(file, F_OK) == 0)
		return (file);
	while (env[i] != NULL)
	{
		if (str_ncmp(env[i], "PATH=", 5) == 0)
		{
			paths = str_dup(env[i] + 5);
			f_paths = strtok(paths, ":");
			while (f_paths)
			{
				ptr_path = str_cpy(path, f_paths);
				ptr_path = str_cat(path, "/");
				ptr_path = str_dup(str_cat(path, file));
				if (access(ptr_path, X_OK) == 0)
				{
					free(paths);
					return (ptr_path);
				}
				free(ptr_path);
				f_paths = strtok(NULL, ":");
			}
			free(paths);
		}
		i++;
	}
	return (NULL);
}
