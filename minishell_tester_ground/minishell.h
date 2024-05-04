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
	int dec;
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
	NO_QUOTE,
	SINGLE,
	DOUBLE
} t_quote_status;

int	lexer(char *user_input, t_cmd **line);
t_quote_status	get_quote_status(char c, t_quote_status stat);
int	is_pipe(char c);
int	check_for_unclosed_quotes(char *str);

t_cmd	*arg_last(t_cmd *lst);
void	arg_add_back(t_cmd **stack, t_cmd *new);
void	init_node(t_cmd *new);

void	print_list(t_cmd **head);
void	free_list(t_cmd *head);
int	argument_into_struct(char *str, t_cmd **line);

char	**ft_split_cmd(char const *s, char c);
void	initialize_arguments(t_cmd **line, char **user);

#endif
