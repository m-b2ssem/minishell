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

typedef enum token_status
{
	NON, // init type
	// first round of checks
	BUILTIN,   // string matches a builtin
	D_QUOTE,   // string inside double quotes, can also be ""
	S_QUOTE,   // string inside single quotes, can also be ''
	HERE_DOC,  // string is <<
	APPEND,    // string matches >>
	REDIR_IN,  // string matches <
	REDIR_OUT, // string matches >
	//second round of checks
	ARG,// string w/o any special (type can be changed)
	A_FILE, // string after >>
	DELIM  // string after a heredoc
} t_token_status;

typedef struct s_env
{
	char *name;
	char *value;
	int dec;
	struct s_env *next;
} t_env;

typedef struct s_token
{
	char *string;
	int expansion;
	t_token_status type;
	struct s_token *next;
} t_token;

typedef struct s_cmd
{
	char **env;
	char *args;
	char **arg_arr;
	int fd_in;
	int fd_out;
	char *eof_file;
	// char *path;
	t_token *token;
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

void	free_list(t_cmd *head);
// int	argument_into_struct(char *str, t_cmd **line);

char	**ft_split_cmd(char const *s, char c);
void	initialize_arguments(t_cmd **line, char **user);
void	iterate_through_cmd_args(t_cmd **line);
int	split_into_tokens(t_cmd **line);
void	get_redirection(char *str, int *i);

void	init_node_tokens(t_token *new);

int	is_redirection(char c);
int	is_other_separator(char c);
void	get_quote_words(char *str, int *i, t_quote_status stat);
void	get_arguments(char *str, int *i, t_quote_status stat);

t_token	*token_last(t_token *lst);
void	token_add_back(t_token **begin, t_token *new);
int	initialize_tokens(char *arg, t_token **type);
t_token	*new_token(char *arg, t_token *new);
void	init_node_tokens(t_token *new);
void	print_list(t_cmd *head);

int	token_type_builtin(char *s);
void	token_type(t_token *tok);
int	decide_token_type(t_cmd **line); 




#endif
