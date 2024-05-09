
#ifndef MINISHELL_H
# define MINISHELL_H

/*MINISHELL LIBRARIES*/
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

/*MINISHELL ENUMS*/

typedef enum mode_status
{
	INTERACTIVE
}					t_mode_status;

typedef enum token_status
{
	NON,     // init type
	BUILTIN, // string matches a builtin
	D_QUOTE, // string inside double quotes, can also be ""
	S_QUOTE, // string inside single quotes, can also be ''
	ARG,
	// string w/o any special (can be changed into files after a redirection symbol)
	HERE_DOC,  // string matches <<
	APPEND,    // string matches >>
	REDIR_IN,  // string matches <
	REDIR_OUT, // string matches >
	INFILE,    // string after <
	OUTFILE,   // string after >
	A_FILE,    // string after >>
	DELIM      // string after a <<
}					t_token_status;

typedef enum quote_status
{
	NO_QUOTE,
	SINGLE,
	DOUBLE,
}					t_quote_status;

/*MINISHELL STRUCTS*/

typedef struct s_env
{
	char			*name;
	char			*value;
	int				declare;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*string;
	int expansion; // -1 for init , 0 for false 1 for true
	t_token_status	type;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
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

}					t_cmd;

/*PARSING*/

/*Helper/Debugging*/
void				print_list(t_cmd *head);

/*Creating the cmd list*/
void				initialize_arguments(t_cmd **line, char **user);
char				**ft_split_cmd(char const *s, char c);
void				init_node(t_cmd *new);
t_cmd				*init_new_node(char *arr, t_cmd *new);
void				arg_add_back(t_cmd **stack, t_cmd *new);
t_cmd				*arg_last(t_cmd *lst);
void				free_list(t_cmd *head);
int					is_redirection(char c);
int					is_other_separator(char c);
void				get_redirection(char *str, int *i);
void				get_arguments(char *str, int *i);
void				get_string_in_quotes(char *str, int *i);
int					is_quotes(char c);

/*Creating the token list*/
int					split_into_tokens(t_cmd **line);
void				iterate_through_cmd_args(t_cmd **line);
void				init_node_tokens(t_token *new);
t_token				*new_token(char *arg, t_token *new);
int					token_type_builtin(char *s);
void				token_type(t_token *tok);
int					decide_token_type(t_cmd **line);
int					initialize_tokens(char *arg, t_token **type);
void				token_add_back(t_token **begin, t_token *new);
t_token				*token_last(t_token *lst);

/*Quote Handling*/
int					check_for_unclosed_quotes(char *str);
t_quote_status		get_quote_status(char c, t_quote_status stat);

/*Redirections*/
int					heredoc_usage(t_cmd **line);
void				change_redirection_relation(t_token *tok, int *redir);
void				change_redir_relation(t_token *tok, int *redir);
int					is_type_arg(t_token *tok);
int					is_type_redir(t_token *tok);
int					redirection_spell_check(t_cmd **line);
int					redirection_spell_check(t_cmd **line);
int					is_pipe(char c);
int					is_space(char c);

/*Free and Error*/
void				free_str(char *str);

#endif
