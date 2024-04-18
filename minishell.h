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


typedef struct		s_cmd t_cmd;


typedef struct s_rid
{
	int	REDIR_IN;
	int REDIR_DIN;
	int REDIR_OUT;
	int REDIR_DOUT;
} t_rid;


typedef struct		s_token
{
	char			*builtin;
	t_rid			type;
	char			*path;
	struct s_token	*next;
}					t_token;

typedef struct		s_cmd
{
	t_token			*token;
	char			**env;
	char			*args;
	char			**arg_arr;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	char			*path;
	struct s_cmd	*next;
}           t_cmd;

int 	redirections(t_cmd *cmd);
int		builtin_pwd();
int		builtin_cd(t_cmd *cmd);
int     builtin_echo(t_cmd *cmd);
int     builtin_export(t_cmd *cmd);
int     builtin_env(char **env);
int     builtin_unset(t_cmd *cmd, char *unset);
int		heredoc(t_cmd *cmd, t_token *token);

// exec
int    execute(t_cmd *cmd, char **env);
int    custom_exe(t_cmd *cmd, char **env)

// utils
int cmd_lenth(t_cmd *cmd);

#endif