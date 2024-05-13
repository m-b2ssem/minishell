
#include "../minishell.h"

int	parse_cmd(char *str, t_cmd **line, t_env *env)
{
	char	**arr;
	int		quote;

	quote = check_for_unclosed_quotes(str);
	if (quote != 0)
	{
		ft_putstr_fd(QUOTES, 1);
		return (free_list(&env));
	}
	else
	{
		arr = ft_split_cmd(str, '|');
		if (arr == NULL)
			return (free_list(&env));
		initialize_arguments(line, arr, env);
		iterate_through_cmd_args(line);
		decide_token_type(line);
		if (redirection_spell_check(line) == 1)
		{
			ft_putstr_fd(REDIR, 1);
			free_everything(line);
			return (free_list(&env));
		}
		search_quotes_modify(line);
		join_quoted_strings(line);
		heredoc_usage(line);
		organise_arg(line);
	}
	return (0);
}
