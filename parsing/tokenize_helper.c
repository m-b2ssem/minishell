#include "../minishell.h"

void	get_string_in_quotes(char *str, int *i)
{
	t_quote_status	stat;

	stat = NO_QUOTE;
	while (str[(*i)])
	{
		stat = get_quote_status(str[(*i)], stat);
		if (is_quotes(str[(*i)]) && stat == NO_QUOTE)
			break ;
		(*i)++;
	}
}

void	get_redirection(char *str, int *i)
{
	char	c;

	c = str[*i];
	while (str[(*i)] && str[(*i)] == c)
		(*i)++;
}

void	get_arguments(char *str, int *i)
{
	t_quote_status	stat;

	stat = NO_QUOTE;
	while (str[(*i)])
	{
		stat = get_quote_status(str[(*i)], stat);
		if (is_other_separator(str[(*i)]) && stat == NO_QUOTE)
			break ;
		else if (is_other_separator(str[(*i)]) && stat != NO_QUOTE)
			break ;
		(*i)++;
	}
}

