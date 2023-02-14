#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct s_ppx
{

	char **cmd_path;
	char **value_splitted; // memory allocated in ft_split
	char ***cmd_args;
	int in;
	int out;

} t_ppx;

char **ft_split(char const *s, char c);
char *ft_strjoin(char const *s1, char c, char const *s2);
void free_array(char **array);

#endif