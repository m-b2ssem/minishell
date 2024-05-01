/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/04/11 15:39:27 by amirfatt          #+#    #+#             */
/*   Updated: 2024/04/14 12:43:49 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define HOME "/Users/bassem"

typedef struct s_cmd t_cmd;

typedef struct s_rid
{
	int REDIR_IN;
	int REDIR_DIN;
	int REDIR_OUT;
	int REDIR_DOUT;
} t_rid;

typedef struct s_env
{
	char *name;
	char *value;
	int export;
	struct s_env *next;
} t_env;

typedef struct s_token
{
	char *builtin;
	t_rid type;
	char *path;
	struct s_token *next;
} t_token;

typedef struct s_cmd
{
	t_token *token;
	char **env;
	char *args;
	char **arg_arr;
	int fd_in;
	int fd_out;
	char *name_file;
	char *path;
	struct s_cmd *next;
} t_cmd;

typedef enum quote_status
{
	SINGLE,
	DOUBLE,
	NO_QUOTE
} t_quote_status;

int	redirections(t_cmd *cmd);
int	builtin_pwd(void);
int	builtin_cd(t_cmd *cmd);
int	builtin_echo(t_cmd *cmd);
int	builtin_export(t_cmd *cmd);
int	builtin_env(char **env);
void	initialize_env_variables(t_env **head, char **env);
int	builtin_unset(t_cmd *cmd, char *unset);
void	builtin_exit(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id);
int	heredoc(t_cmd *cmd, t_token *token);

// exec
int	execute(t_cmd *cmd, char **env);
int	custom_exe(t_cmd *cmd, char **env, t_cmd *tmp, pid_t *pross_id);
int	child_procces(t_cmd *cmd, pid_t *pross_id, int i, t_cmd *tmp);
void	custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp);
int	piping(t_cmd *cmd);

// utils
int	cmd_lenth(t_cmd *cmd);
int	close_fd(t_cmd *cmd);
void	wait_pid(pid_t *pross_id, int len);
char	*get_bin_path(char *command);
void	free_cmd(t_cmd *cmd);
void	clean_exit(t_cmd *tmp, pid_t *pross_id, int status);
void	print_list(t_env *head);
void	free_list(t_env *head);

// parsing

#endif
