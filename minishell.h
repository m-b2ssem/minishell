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

typedef struct		s_cmd t_cmd;

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

typedef struct		s_token
{
	char			*string;
	int 			expansion;
	t_token_status	type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*name;
	char			*value;
	int				export;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	t_env			*env;
	t_token			*token;
	char			**arg_arr;
	int				fd_in;
	int				fd_out;
	char *args; 
	char			*file;
	char			*path;
	int				exit_status;
	struct s_cmd	*next;
}           t_cmd;

int 	redirections(t_cmd *cmd);
int		builtin_pwd();
int		builtin_cd(t_cmd *cmd);
int     builtin_echo(t_cmd *cmd);
int     builtin_export(t_cmd *cmd);
int     builtin_env(t_env *env);
int 	builtin_unset(t_env **head, t_cmd *cmd);
int		builtin_exit(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id);
int		heredoc(t_cmd *cmd);

// exec
int    execute(t_cmd **cmd, t_env *env);
int    custom_exe(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id);
int 	child_process(t_cmd *cmd,  pid_t *pross_id, int i, t_cmd *tmp);
void    custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp);
int 	piping(t_cmd *cmd);

// utils
int cmd_lenth(t_cmd *cmd);
int close_fd(t_cmd *cmd);
int wait_pid(pid_t *pross_id, int len);
char *get_path(char *command);
void free_cmd(t_cmd *cmd);
void clean_exit(t_cmd *tmp, pid_t *pross_id, int status);
int    builtin(t_cmd *cmd);
void    signal_handler(int signum);
int last_exit_status(int *exit_statuses, int len);
char   *check_for_env_value(char *str, t_env *env);

/* signals */
void	child_signal(void);
void	parent_signals(void);

void				initialize_env_variables(t_env **head, char **env);
void				free_list(t_env **head);
t_env				*lst_last(t_env *lst);
t_env				*lst_new(char *name, char *value, t_env *new, int export);
void				lst_addback(t_env **list, t_env *new);



// alja 

void				print_list_env(t_env *head);
void				print_list(t_cmd **head); 
t_env				*lst_last(t_env *lst);
void				lst_addback(t_env **list, t_env *new);
int					find_char(char *s);
void				free_list_env(t_env *head);

/*Creating the cmd list*/
void				initialize_arguments(t_cmd **line, char **user);
char				**ft_split_cmd(char const *s, char c);
void				init_node(t_cmd *new);
t_cmd				*init_new_node(char *arr, t_cmd *new);
void				arg_add_back(t_cmd **stack, t_cmd *new);
t_cmd				*arg_last(t_cmd *lst);
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

/*HELPER*/
int					organise_arg(t_cmd **cmd);
void				initialize_env_variables(t_env **head, char **env);
int					the_expander(t_cmd **line);
void				update_eof_expansion(t_token *tok);
int					the_expander(t_cmd **line); 
char				*create_expansion(t_env *curr, char *org, int start,
						char *tmp);
char				*get_env_value(char *new, char *org, t_env **list, int *i);
char				*double_quote_expansion(t_token *tok, char *str, char *new);
int					update_string_expansion(t_token *tok);

#endif
