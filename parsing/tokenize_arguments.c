
#include "../minishell.h"

int	split_into_tokens(t_cmd **line)
{
	char			*arg;
	int				size;
	t_quote_status	stat;
	t_cmd			*curr;
	int				start;
	int				i;

	arg = NULL;
	curr = *line;
	size = ft_strlen(curr->args);
	if (size == 0)
		return (1);
	stat = NO_QUOTE;
	start = 0;
	i = 0;
	while (i < size)
	{
		start = i;
		if (is_redirection(curr->args[i]) && stat == NO_QUOTE)
			get_redirection(curr->args, &i);
		else if (is_quotes((curr->args[i])))
		{
			get_string_in_quotes(curr->args, &i);
			++i;
		}
		else if (is_space(curr->args[i]))
			i++;
		else
			get_arguments(curr->args, &i);
		arg = ft_substr(curr->args, start, i - start);
		if (initialize_tokens(arg, (&curr->token)) == 1)
			return (1);
	}
	return (0);
}

int	iterate_through_cmd_args(t_cmd **line)
{
	t_cmd	*current;

	current = *line;
	while (current != NULL)
	{
		if (split_into_tokens(&current) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}
