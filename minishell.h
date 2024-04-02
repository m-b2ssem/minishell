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

#define HOME "gg"

typedef struct		s_cmd t_cmd;


typedef struct s_value
{
	int	REDIR_IN;
	int REDIR_DIN;
	int REDIR_OUT;
	int REDIR_DOUT;
} t_value;


typedef struct		s_token
{
	t_value			type;
	char			*path;
	struct s_token	*next;
}					t_token;

typedef struct		s_cmd
{
	char			*string;
	t_token			*token;
	char			**env;
	char			*args;
	char			**arg_arr;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	char			*builtin;
	char			*path;
	//s_cmd	        *next;
}           t_cmd;

int 	redirections(t_cmd *cmd);
int		builtin_pwd();
int		builtin_cd(t_cmd *cmd);
void    custom_exe(t_cmd *cmd, char **env);
int     builtin_echo(t_cmd *cmd);
int     builtin_export(t_cmd *cmd);
int     builtin_env(char **env);
int     builtin_unset(t_cmd *cmd, char *unset);

#endif