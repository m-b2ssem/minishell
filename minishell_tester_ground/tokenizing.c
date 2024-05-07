
#include "minishell.h"

void	print_list(t_cmd *head)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = head;
	while (cmd != NULL)
	{
		printf("Node: %s\n", cmd->args);
		tok = cmd->token;
		while (tok != NULL)
		{
			printf("\tTOK: %s\n", tok->string);
			printf("\tTYPE: %d\n", tok->type);
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}

void	iterate_through_cmd_args(t_cmd **line)
{
	t_cmd	*current;

	current = *line;
	while (current != NULL)
	{
		if (split_into_tokens(&current) > 0)
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
	if (c == ' ' || c == '	' || c == '<' || c == '>' || c == '\'' || c == '"')
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

int	split_into_tokens(t_cmd **line)
{
	char			*arg;
	int				size;
	t_quote_status	stat;
	t_cmd			*curr;
	int				flag;
	int				start;
	int				i;

	arg = NULL;
	curr = *line;
	size = ft_strlen(curr->args);
	if (size == 0)
		return (-1);
	stat = NO_QUOTE;
	flag = 0;
	start = 0;
	i = 0;
	while (i < size)
	{
		while (curr->args[i] && curr->args[i] == ' ')
			i++;
		// stat = get_quote_status(curr->args[i], stat);
		start = i;
		if (is_redirection(curr->args[i]) && stat == NO_QUOTE)
			get_redirection(curr->args, &i);
		else if (is_quotes((curr->args[i])))
		//&& (stat == SINGLE|| stat == DOUBLE))
		{
			get_string_in_quotes(curr->args, &i);
			++i;
			// if (curr->args[i + 1] != ' ')
			// 	++i;
		}
		else
			get_arguments(curr->args, &i);
		// if (is_quotes(curr->args[i]))
		// 	stat = get_quote_status(curr->args[i], stat);
		arg = ft_substr(curr->args, start, i - start);
		// printf("\n\nArg is::: %s\n\n", arg);
		if (initialize_tokens(arg, (&curr->token)) == -1)
			return (-1);
	}
	return (0);
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
