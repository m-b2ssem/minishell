
#include "minishell.h"


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
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);

		//str = readline(PROMPT);
		// if (isatty(fileno(stdin)))
		// 	str = readline(str);
		// else
		// {
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	str = ft_strtrim(line, "\n");
		// 	if(!str)
		// 		break;
		// 	free(line);
		// }
		if (str == NULL)
		{
			free_list(&envp);
			return (0);
		}
		add_history(str);
		if (parse_cmd(str, &cmd, envp) == 1)
		{
			free_list(&envp);
			free_everything(&cmd);
			exit(0);
		}
		execute(&cmd);
		free_everything(&cmd);
	}
	free_list(&envp);
	free_everything(&cmd);
	return (0);
}
