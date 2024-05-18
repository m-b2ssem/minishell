#ifndef MINISHELL_H
# define MINISHELL_H

# include "library/get_next_line/include/get_next_line.h"
# include "library/libft/include/libft.h"
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
# define PROMPT "minishell $> "
# define QUOTES "minishell: syntax error: unclosed quotes detected\n"
# define REDIR "minishell: syntax error near unexpected token\n"

typedef struct s_cmd t_cmd;

typedef enum mode_status
{
	INTERACTIVE
} t_mode_status;

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
	DELIM,     // string after a <<
	BLANK,
	OPTION
} t_token_status;

typedef enum slash_status
{
	NO_SLASH,
	OPEN
} t_slash_status;

typedef enum quote_status
{
	NO_QUOTE,
	SINGLE,
	DOUBLE,
} t_quote_status;

typedef struct s_token
{
	char *string;
	int expansion;
	int join;
	t_token_status type;
	struct s_token *next;
} t_token;

typedef struct s_env
{
	char *name;
	char *value;
	int export;
	struct s_env *next;
} t_env;

typedef struct s_cmd
{
	t_env *env;
	t_token *token;
	char **arg_arr;
	int fd_in;
	int fd_out;
	char *args;
	char *file;
	char *path;
	int exit_status;
	struct s_cmd *next;
} t_cmd;

int	redirections(t_cmd *cmd);
int	builtin_pwd(void);
int	builtin_cd(t_cmd *cmd);
int	builtin_echo(t_cmd *cmd);
int	builtin_export(t_cmd *cmd);
int	builtin_env(t_env *env);
int	builtin_unset(t_env **head, t_cmd *cmd);
int	builtin_exit(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id);
int	heredoc(t_cmd *cmd, char *word);

// exec
int	execute(t_cmd **cmd1);
int	custom_exe(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id);
void	custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp);
int	piping(t_cmd *cmd);
int	join_quoted_helper(t_token *curr_tok);

// utils
int	cmd_lenth(t_cmd *cmd);
int	close_fd(t_cmd *cmd);
int	wait_pid(pid_t *pross_id, int len);
char	*get_path(char *command, t_env *env);
void	free_cmd(t_cmd *cmd);
void	clean_exit(t_cmd *tmp, pid_t *pross_id, int status);
int	builtin(t_cmd *cmd);
void	signal_handler(int signum);
int	last_exit_status(int *exit_statuses, int len);
char	*check_for_env_value(char *str, t_env *env);
void	free_list_tokens(t_token **head);
int	env_len(t_env *env);
char	**env_to_char(t_env *env);
int	one_operation(t_cmd *cmd, t_cmd *tmp, pid_t *pross_ids);
void	loop_inside_execute(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp);
char	*my_getenv(char *name, t_env *env);

/* signals */
void	child_signal(void);
void	parent_signals(void);
void	sig_ign(void);

int	free_list(t_env **head);
t_env	*lst_last(t_env *lst);
t_env	*lst_new(char *name, char *value, t_env *new, int export);
void	lst_addback(t_env **list, t_env *new);

/*//////////////////////////////////////////////////////////////////////////////////////*/
/*/////////////////////////////NEW HEADER FILES ORGANISATION////////////////////////////*/
/*//////////////////////////////////////PLEASE KEEP/////////////////////////////////////*/

/*ENVIRONMENT FOLDER*/
/*ENV_LIST.c*/
t_env	*initialize_env_variables(t_env **head, char **env);
void	lst_addback(t_env **list, t_env *new);
t_env	*lst_new(char *name, char *value, t_env *new, int export);
t_env	*lst_last(t_env *lst);

/*PARSING FOLDER*/
/*SPLIT_CMD.c*/
char	**ft_split_cmd(char const *s, char c);

/*START_PARSE.c*/
int	parse_cmd(char *str, t_cmd **line, t_env *env);

/*START_PARSE_CHECKER.c*/
int	first_string_checks(char *str);
int	check_for_empty(char *str);
int	check_unexpected_token(char *str);
int	check_for_unclosed_quotes(char *str);

/*INIT_ARGUMENTS.c*/
int	initialize_arguments(t_cmd **line, char **user, t_env *env);
t_cmd	*init_new_node(char *arr, t_cmd *new, t_env *env);
void	init_node(t_cmd *new, t_env *list);
void	arg_add_back(t_cmd **stack, t_cmd *new);
t_cmd	*arg_last(t_cmd *lst);

/*INIT_TOKENS.c*/
int	initialize_tokens(char *arg, t_token **type);
t_token	*new_token(char *arg, t_token *new);
void	init_node_tokens(t_token *new);
void	token_add_back(t_token **begin, t_token *new);
t_token	*token_last(t_token *lst);

/*TOKENIZE_ARGUMENTS.c*/
int	iterate_through_cmd_args(t_cmd **line);
int	split_into_tokens(t_cmd **line);

/*TOKENIZE_HELPER.c*/
void	get_arguments(char *str, int *i);
void	get_redirection(char *str, int *i);
void	get_string_in_quotes(char *str, int *i);
t_quote_status	get_quote_status(char c, t_quote_status stat);

/*TOKENIZE_HELPER_TWO.c*/
int	is_redirection(char c);
int	is_other_separator(char c);
int	is_quotes(char c);
int	is_space(char c);
int	find_char(char *s);

/*TOKEN_TYPE.c*/
int	decide_token_type(t_cmd **line);
void	token_type(t_token *tok);
int	token_type_builtin(char *s);

/*REDIRECTION_SPELL_CHECK.c*/
int	redirection_spell_check(t_cmd **line);
int	is_type_redir(t_token *tok);

/*TRIM_QUOTES.c*/
int	search_quotes_modify(t_cmd **line);
int	update_quote_strings(t_token *tok);

/*EXPANSION.C*/
int	handle_expansion(t_cmd **line);
void	possible_expansion(t_cmd **cmd, t_token *tok);
char	*get_env_value(char *tmp_name, t_token *tok, t_env **list, int start);
char	*create_expansion(t_env *curr, char *org, int start, char *tmp);
char	*forbidden_variable_name(t_token *tok, char *tmp, int start);

/*EXPANSION_HELPER.C*/
int	calculate_size(t_env *curr, char *org, char *tmp);
t_env	*find_accord_env_name(char *tmp, t_env **list);
int	is_valid_char_rest(char c);
int	is_valid_char_begin(char c);

/*QUOTE_JOINING.c*/
int	join_quoted_strings(t_cmd **head);
int	assign_join_variable(t_cmd **cmd);
int	find_node_and_modify(char *join, t_token **tok, t_token *find);
int	assign_join_variable(t_cmd **cmd);
char	*join_strings(t_token **head);

/*QUOTE_JOIN_HELPER.c*/
int	find_and_modify_unused_nodes(t_token *tok);
int	join_quoted_helper(t_token *curr_tok);
int	join_redir_helper(t_token *token);

/*REDIR_RELATIONS.c*/
int	redirection_usage(t_cmd **line);
void	change_redirection_relation(t_token *tok, int *redir);
void	change_redir_relation(t_token *tok, int *redir);
int	is_type_arg(t_token *tok);

/*CREATE_ARRAY_EXEC.c*/
int	create_arr_for_exec(t_cmd **line);
int	count_arg(t_cmd *cmd);
void	initialize_arg_array(t_cmd *cmd);

/*ECHO_EDGECASE.c*/
int	echo_option_checker(t_cmd **line);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	validate_echo_option(char *str);
void	modify_echo_option(t_token *tok);

/*FREE_SHELL.c*/
void	free_everything(t_cmd **line);
void	free_env_list(t_env *head);
void	free_list_tokens(t_token **head);
int	free_list(t_env **head);

/*FT_HELPER.c*/
void	print_list(t_cmd **head);
void	print_arr(t_cmd **cmd);

/*HANDLE_BACKSLASH.c*/
t_slash_status	get_backslash_status(char c, t_slash_status stat);
void	modify_string_backslash(t_token *tok, char *str);
int	handle_backslash(t_cmd **line);


#endif
