
#include "minishell.h"

int	check_for_unclosed_quotes(char *str)
{
	int				i;
	t_quote_status	stat;
	t_quote_status	dominant;
	int				j;

	i = 0;
	stat = NO_QUOTE;
	dominant = NO_QUOTE;
	while (str[i])
	{
		stat = get_quote_status(str[i], stat);
		if (stat == SINGLE || stat == DOUBLE)
		{
			if (dominant == NO_QUOTE)
				dominant = stat;
			else if (dominant == stat)
			{
				if (str[i + 1] == str[i])
					dominant = NO_QUOTE;
				else
				{
					j = i + 1;
					while (str[j])
					{
						if (get_quote_status(str[j], stat) == dominant)
							break ;
						j++;
					}
					if (str[j] == '\0')
						return (dominant);
				}
			}
		}
		i++;
	}
	return (NO_QUOTE);
}

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
	return (end);
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
	quote = NO_QUOTE;
	end = 0;
	start = 0;
	i = 0;
	if (!user_input || *user_input == 0)
		return (-1);
	while (user_input[i] != '\0')
	{
		while (is_space(user_input[i]) && user_input[i] != '\0')
			i++;
		if ((size_t)i == ft_strlen(user_input) - 1)
			break ;
		end = find_pipe(user_input, i, quote);
		if (end >= 0)
		{
			arg = ft_substr(user_input, i, end);
			if (!arg)
				return (-1);
			if (arg && *arg != '\0')
			{
				argument_into_struct(arg, line);
				free(arg);
			}
			else if (arg)
				free(arg);
			i = i + end;
		}
		else if (end == -1 && (size_t)i != ft_strlen(user_input))
		{
			start = start + i;
			arg = ft_substr(user_input, start, ft_strlen(user_input) - start);
			if (!arg)
				return (-1);
			if (arg && *arg != '\0')
				argument_into_struct(arg, line);
			else if (arg)
				free(arg);
			free(arg);
		}
		i++;
	}
	return (0);
}

void	init_node(t_cmd *new)
{
	new->token = NULL;
	new->args = NULL;
	new->arg_arr = NULL;
	new->name_file = NULL;
	new->path = NULL;
}

int	argument_into_struct(char *str, t_cmd **line)
{
	t_cmd	*new;

	new = NULL;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	init_node(new);
	if (str == NULL)
	{
		free(new);
		return (0);
	}
	new->args = ft_strdup(str);
	if (!new->args)
	{
		free(new);
		free_list(line);
		return (0);
	}
	arg_add_back(line, new);
	return (0);
}

void	arg_add_back(t_cmd **stack, t_cmd *new)
{
	t_cmd	*current;

	current = NULL;
	if (stack)
	{
		if (*stack == NULL)
			*stack = new;
		else
		{
			current = arg_last(*(stack));
			current->next = new;
		}
		// new = NULL;
	}
}

void	print_list(t_cmd *head) // Single pointer to head
{
	if (head == NULL)
	{
		printf("List is empty\n");
		return ;
	}

	t_cmd *current = head;
	while (current != NULL)
	{
		printf("    Name: %s\n", current->args);
		current = current->next;
	}
	printf("NULL\n");
}

t_cmd	*arg_last(t_cmd *lst)
{
	t_cmd	*current;

	current = NULL;
	if (lst == NULL)
		return (NULL);
	current = lst;
	while (current->next != 0)
	{
		current = current->next;
	}
	return (current);
}

void	free_list(t_cmd **head)
{
	t_cmd	*current;
	t_cmd	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->args);
		free(current);
		current = next;
	}
}
