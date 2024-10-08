
#include "../minishell.h"

int	check_for_unclosed_quotes(char *str)
{
	int				i;
	t_quote_status	stat;

	i = 0;
	stat = NO_QUOTE;
	while (str[i])
	{
		stat = get_quote_status(str[i], stat);
		i++;
	}
	return (stat);
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

int	first_string_checks(char *str)
{
	int	quote;
	int	token;

	quote = 0;
	token = 0;
	quote = check_for_unclosed_quotes(str);
	if (quote != 0)
	{
		ft_putstr_fd(QUOTES, 2);
		return (1);
	}
	token = check_unexpected_token(str);
	if (token != 0)
	{
		ft_putstr_fd(REDIR, 2);
		return (1);
	}
	return (0);
}
