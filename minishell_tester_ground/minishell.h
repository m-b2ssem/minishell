

#ifndef TEST_H
# define TEST_H

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

int					is_type_redir(t_token *tok);
int					redirection_spell_check(t_cmd **line);
int					is_type_arg(t_token *tok);
void				change_redir_relation(t_token *tok, int *redir);
void				change_redirection_relation(t_token *tok, int *redir);
int					heredoc_usage(t_cmd **line);
void				free_str(char *str);
int					check_for_unclosed_quotes(char *str);
int					is_pipe(char c);
t_quote_status		get_quote_status(char c, t_quote_status stat);
int					is_space(char c);
void				arg_add_back(t_cmd **stack, t_cmd *new);
t_cmd				*arg_last(t_cmd *lst);
void				free_list(t_cmd *head);
void				init_node_tokens(t_token *new);
void				iterate_through_cmd_args(t_cmd **line);
int					split_into_tokens(t_cmd **line);
int					is_quotes(char c);
t_token				*new_token(char *arg, t_token *new);
int					token_type_builtin(char *s);
int					decide_token_type(t_cmd **line);
void				token_type(t_token *tok);
int					initialize_tokens(char *arg, t_token **type);

void				print_list(t_cmd *head);
int					the_expander(t_cmd **line);
char				**ft_split_cmd(char const *s, char c);
void				init_node(t_cmd *new);
t_cmd				*init_new_node(char *arr, t_cmd *new);
void				initialize_arguments(t_cmd **line, char **user);
void				token_add_back(t_token **begin, t_token *new);
t_token				*token_last(t_token *lst);

char				*ft_get_value_of_env(t_env **env, char *str);
int					ft_get_lenkey(char *env);
t_env				**get_adress_env(void);
char				*ft_get_env(char *str);
char				*fake_env(int *j, int len_str);
char				*if_no_env(char *str, char *s1, int *cur);
int					get_len_env_var(char *str);
char				*if_env(char *str, char *s1, int *cur);
char				*word_will_single(char *str, int *i, char *s1);
char				*free_str_ret_null(char *s1);

char				*word_will_unquote(t_token **stc, char *str, int *cur,
						char *s1);
int					end_modif_two(char *str, t_token **stc, char *s1);
int					free_str_ret_malloc_error(char *str);
char				*word_will_double(char *str, int *cur, char *s1);
char				*init_str(char **str, char *duplica, int *cur, char **s1);

int					word_modif_two(t_token **stc, char *duplica,
						t_quote_status quote, t_quote_status prec);
int					move_to(char *str, int *i, t_quote_status quote);
void				free_both(char *s1, char *s2);
char				*expand_full_quote_str(void);
char				*limitor_unquote(char *str, int *i, char *s1,
						t_quote_status quote);
t_quote_status		update_quote_succes(t_token *stc, int *i,
						t_quote_status quote, char **s1);
t_quote_status		update_quote_status(char c, t_quote_status quote);
char				*devellope_limitor(t_token *stc, char *str, int i);
int					limitor(t_token *stc, char *str);
int					word_modif(t_token **stc, char *str, t_token_status token);
int					expend_words(t_cmd **block);

#endif
