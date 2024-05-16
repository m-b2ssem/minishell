
#include "minishell.h"


<<<<<<< HEAD
void	print_list_env(t_env *head)
=======
int	parse_cmd(char *str, t_cmd **line, t_env *env, int status)
>>>>>>> main
{
	t_env *current;

<<<<<<< HEAD
	current = head;
=======
	printf("status: %d\n", status);
	res = check_for_unclosed_quotes(str);
	if (res != 0)
	{
		printf("Result %d\n", res);
		printf("Unclosed detected\n");
	}
	else
	{
		arr = ft_split_cmd(str, '|');
		initialize_arguments(line, arr, env);
		iterate_through_cmd_args(line);
		decide_token_type(line);
		if (redirection_spell_check(line) == -1)
		{
			printf("Syntax error in redirection\n");
		}
		// if (heredoc_usage(line) == -1)
		// {
		// 	printf("WRONG__________\n");
		// }
		the_expander(line);
		try_solve_join(line);

		organise_arg(line);
	}
	return (0);
}

void	free_list_tokens(t_token **head)
{
	t_token *current;
	t_token *tmp;

	current = *head;
>>>>>>> main
	while (current != NULL)
	{
		printf("Name: %s\n", current->name);
		printf("Value: %s\n", current->value);
		current = current->next;
	}
}

t_quote_status	get_quote_status(char c, t_quote_status stat)
{
	if (c == '\'' && stat != SINGLE && stat != DOUBLE)
		stat = SINGLE;
	else if (c == '"' && stat != DOUBLE && stat != SINGLE)
		stat = DOUBLE;
	else if ((c == '\'' && stat == SINGLE) || (c == '"' && stat == DOUBLE))
		stat = NO_QUOTE;
	return (stat);
}

int	check_for_unclosed_quotes(char *str)
{
	int i;
	t_quote_status stat;

	i = 0;
	stat = NO_QUOTE;
	while (str[i])
	{
		stat = get_quote_status(str[i], stat);
		i++;
	}
	return (stat);
}

void	free_env_list(t_env *head)
{
	t_env *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **env)
{
	int status = 0;
	char *str;
	t_cmd *cmd = NULL;
	t_env *envp = NULL;

	if (!argc && !argv)
		return (0);
	envp = initialize_env_variables(&envp, env);
	if (envp == NULL)
		return (0);
	while (1)
	{
<<<<<<< HEAD
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
=======
		str = readline("minishell>");
>>>>>>> main
		if (str == NULL)
		{
			free_list(&envp);
			return (0);
<<<<<<< HEAD
		}
		add_history(str);
		if (parse_cmd(str, &cmd, envp) == 1)
		{
			free(str);
			free_list(&envp);
			free_everything(&cmd);
			return (1);
		}
		status = execute(&cmd, envp);
		//print_list(&cmd);
		printf("\nStatus: %d\n", status);
=======
			free_everything(&cmd);
		}
		add_history(str);
		parse_cmd(str, &cmd, envp, status);
		status = execute(&cmd);
>>>>>>> main
		free_everything(&cmd);
	}
	free_list(&envp);
	free_everything(&cmd);
	return (0);
}
