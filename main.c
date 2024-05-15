
#include "minishell.h"


void	print_list_env(t_env *head)
{
	t_env *current;

	current = head;
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
	extern char **__environ;
	env = __environ;
	t_cmd *cmd = NULL;
	t_env *envp = NULL;

	if (!argc && !argv)
		return (0);
	envp = initialize_env_variables(&envp, env);
	if (envp == NULL)
		return (0);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		str = readline(PROMPT);
		if (str == NULL)
		{
			free_list(&envp);
			return (0);
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
		printf("Status: %d\n", status);
		// print_list(&cmd);
		free_everything(&cmd);
	}
	free_list(&envp);
	free_everything(&cmd);
	return (0);
}
