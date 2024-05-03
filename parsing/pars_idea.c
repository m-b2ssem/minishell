
#include "../minishell.h"

int	is_pipe(char c)
{
	return (c == '|');
}

t_quote_status	get_quote_status(char c, t_quote_status stat)
{
	if (c == '\'' && stat != SINGLE)
		stat = SINGLE;
	else if (c == '"' && stat != DOUBLE)
		stat = DOUBLE;
	else if ((c == '\'' && stat == SINGLE) || (c == '"' && stat == DOUBLE))
		stat = NO_QUOTE;
	return (stat);
}

void	end_of_process(char *str, int *i)
{
	t_quote_status	quote;

	quote = NO_QUOTE;
	while (str[(*i)])
	{
		quote = get_quote_status(str[(*i)], quote);
		if (is_pipe(str[(*i)]) && quote == NO_QUOTE)
			return ;
		(*i)++;
	}
}

int	lexer(char *user_input, t_cmd **line)
{
	int		i;
	int		start;
	char	*arg;

	(void)line;
	arg = NULL;
	i = 0;
	start = 0;
	while (user_input && user_input[i] != '\0')
	{
		end_of_process(user_input, &i);
		arg = ft_substr(user_input, start, i - start);
		printf("%s\n", arg);
		start = i;
		free(arg);
	}
	return (0);
}
