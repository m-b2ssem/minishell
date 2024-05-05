
#include "minishell.h"

void	iterate_through_cmd_args(t_cmd **line)
{
	t_cmd	*current;

	current = *line;
	while (current != NULL)
	{
		if (split_into_tokens(&current))
			return ;
		current = current->next;
	}
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_other_separator(char c)
{
	if (c == ' ' || c == '	' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	get_redirection(char *str, int *i)
{
	char	c;

	c = str[*i];
	while (str[(*i)] && str[(*i)] == c)
		(*i)++;
}

void	get_quote_words(char *str, int *i, t_quote_status stat)
{
	while (str[(*i)] && stat != NO_QUOTE)
	{
		// printf("QUOTE is %c\n", str[(*i)]);
		stat = get_quote_status(str[(*i)], stat);
		if (stat == NO_QUOTE)
			break ;
		(*i)++;
	}
}
void	get_arguments(char *str, int *i, t_quote_status stat)
{
	while (str[(*i)])
	{
		// printf("QUOTE is %c\n", str[(*i)]);
		stat = get_quote_status(str[(*i)], stat);
		if (is_other_separator(str[(*i)]) && stat == NO_QUOTE)
			break ;
		(*i)++;
	}
}

int	split_into_tokens(t_cmd **line)
{
	int				size;
	int				start;
	int				i;
	t_quote_status	stat;
	t_cmd			*curr;
	char			*arg;

	arg = NULL;
	size = 0;
	start = 0;
	i = 0;
	stat = NO_QUOTE;
	curr = *line;
	if (curr->args != NULL)
		size = ft_strlen(curr->args);
	// printf("%d\n", size);
	while (i < size)
	{
		// printf("I _______%d\n", i);
		while (curr->args[i] && curr->args[i] == ' ')
			i++;
		stat = get_quote_status(curr->args[i], stat);
		start = i;
		if (curr->args[i] && is_redirection(curr->args[i]) && stat == NO_QUOTE)
			get_redirection(curr->args, &i);
		else if (stat == SINGLE || stat == DOUBLE)
			get_quote_words(curr->args, &i, stat);
		else
			get_arguments(curr->args, &i, stat);
		// printf("Start is %d\n", start);
		arg = ft_substr(curr->args, start, i - start);
		if (arg != NULL)
		{
			// printf("Start is %i\n", start);
			printf("ARG is %s\n", arg);
		}
	}
	return (0); 
}
