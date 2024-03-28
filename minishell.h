#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
#include <sys/fcntl.h>

typedef struct s_cmd
{
    char    *path;
    char    *builtin;
} 	t_cmd;

void	redirections(char *cml);
int		builtin_pwd();
int		builtin_cd(t_cmd *cmd);
void    custom_exe(t_cmd *cmd);

#endif