#ifndef MAIN_H
#define MAIN_H

#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 1024

extern char **environ;

/*built in functions*/
int retrieveBuiltIn(char *str);
int built_in(char *command, char *free_line, int proces_stat);
void printEnv(void);

/*mem fuctions*/
void _free(char **args);
char **createBuffer(int num_args, char *command);

/*path functions*/
char *full_path(char *file_name);

/*command line and execution functions*/
char *removeWhitespace(char *previous_line);
int execfile(char *command_line, char *programName);
int getArgumentCount(char *line);
char *locateComment(char *command_line);

/*string functions*/
int str_len(char *str);
char *str_dup(char *str);
char *str_cat(char *dest, char *src);
char *str_cpy(char *dest, char *src);
int str_ncmp(char *str1, char *str2, int n);

#endif /* MAIN_H */
