
#include "../minishell.h"

void	print_arr(t_cmd **cmd)
{
	t_cmd	*curr;
	int		i;

	curr = *cmd;
	i = 0;
	while (curr != NULL)
	{
		if (curr->arg_arr)
		{
			i = 0;
			while (curr->arg_arr[i])
			{
				printf("\t%s\n", curr->arg_arr[i]);
				i++;
			}
		}
		curr = curr->next;
	}
}

int	parse_cmd(char *str, t_cmd **line, t_env *env)
{
	char	**arr;
	int		quote;
	int		token;

	quote = check_for_unclosed_quotes(str);
	if (quote != 0)
	{
		ft_putstr_fd(QUOTES, 1);
		return (1);
	}
	token = check_unexpected_token(str);
	if (token != 0)
	{
		ft_putstr_fd(REDIR, 1);
		return (1);
	}
	else
	{
		arr = ft_split_cmd(str, '|');
		if (arr == NULL)
			return (1);
		initialize_arguments(line, arr, env);
		iterate_through_cmd_args(line);
		decide_token_type(line);
		if (redirection_spell_check(line) == 1)
		{
			ft_putstr_fd(REDIR, 1);
			free(arr);
			return (1);
		}
		search_quotes_modify(line);
		handle_expansion(line);
		join_quoted_strings(line);
		heredoc_usage(line);
		create_arr_for_exec(line);
		print_arr(line);
	}
	return (0);
}

int	check_unexpected_token(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|' && str[i] != '<' && str[i] != '>')
			j = 1;
		else if (str[i] == '|')
		{
			if (j == 0)
				return (1);
			j = 0;
		}
		i++;
	}
	return (0);
}
