
#include "minishell.h"

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
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

// void	tokenize_argument(char *user_input, int *start, int *i, char **arg)
// {
// 	t_quote_status	quote;

// 	quote = NO_QUOTE;
// 	while ((user_input[(*i)] != '\0') /* && !is_pipe(user_input[*i]))
// 		|| quote != NO_QUOTE */)
// 	{
// 		printf("Is_pipe %d\n", is_pipe(user_input[*i]));
// 		if (is_pipe(user_input[*i]))
// 			break ;
// 		quote = get_quote_status(user_input[*i], quote);
// 		(*i)++;
// 	}
// 	*arg = ft_substr(user_input, *start, *i - *start);
// }

int	find_pipe(char *str, int i, t_quote_status quote)
{
	int	start;
	int	end;

	start = i;
	end = 0;
	while (str[start + end])
	{
		quote = get_quote_status(str[start + end], quote);
		if (str[start + end] == '|' && quote == NO_QUOTE)
			return (end);
		else
			end++;
	}
	return (-1);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	lexer(char *user_input, t_cmd **line)
{
	int				i;
	int				end;
	char			*arg;
	t_quote_status	quote;
	int				start;

	arg = NULL;
	(void)line;
	quote = NO_QUOTE;
	end = 0;
	start = 0;
	i = 0;
	arg = ft_strdup("");
	while (user_input[i] != '\0')
	{
		// while (is_space(user_input[i]) && user_input[i] != '\0')
		// 	i++;
		if ((size_t)i == ft_strlen(user_input) - 1)
			break ;
		end = find_pipe(user_input, i, quote);
		// printf("END IS %d\n", end);
		if (end >= 0)
		{
			arg = ft_substr(user_input, i, end);
			printf("ARG (!) is %s\n", arg);
			i = i + end;
		}
		else if (end == -1 && (size_t)i != ft_strlen(user_input))
		{
			// printf("I IS %d\n", i);
			start = start + i;
			// printf("START IS %d\n", i);
			// printf("LENGTH IS %zu\n", ft_strlen(user_input));
			arg = ft_substr(user_input, start, ft_strlen(user_input) - start);
			if (arg)
				printf("ARG (?? ) is %s\n", arg);
		}
		i++;
	}
	return (0);
}
