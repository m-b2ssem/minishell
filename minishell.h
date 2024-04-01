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

#define HOME "/Users/bassem"

/*typedef struct s_cmd
{
    char    **env;
    char    *path;
    char    *builtin;
    char    *args;
    char    **arg_arr;
} 	t_cmd;*/

typedef struct s_cmd t_cmd;
typedef struct		s_cmd
{
	char			*string;
	t_token			*first_token;
	char			**envp;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	s_cmd	        *next;
}           t_cmd;

void	redirections(t_cmd *cml);
int		builtin_pwd();
int		builtin_cd(t_cmd *cmd);
void    custom_exe(t_cmd *cmd, char **env);
int     builtin_echo(t_cmd *cmd);
int     builtin_export(t_cmd *cmd);
int     builtin_env(char **env);
int     builtin_unset(t_cmd *cmd, char *unset);

#endif