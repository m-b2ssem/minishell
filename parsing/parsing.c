
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

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

t_quote_status	get_quote_status(char c, t_quote_status stat)
{
	if (c == '\'' && stat != SINGLE && stat != DOUBLE)
		stat = SINGLE;
	else if (c == '"' && stat != DOUBLE && stat != SINGLE)
		stat = DOUBLE;
	else if ((c == '\'' && stat == SINGLE) || (c == '"' && stat == DOUBLE))
		stat = NO_QUOTE;
	return (stat);
}

int	is_space(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

static int	numwords(char const *s, char c)
{
	int	cur;
	int	word_num;

	cur = 0;
	word_num = 0;
	while (s[cur] != '\0')
	{
		if (s[cur] != c && (s[cur + 1] == c || s[cur + 1] == '\0'))
			word_num++;
		cur++;
	}
	return (word_num);
}

static int	split_words(char **result, char const *s, char c, int word)
{
	int				start_cur;
	int				end_cur;
	t_quote_status	quote;

	end_cur = 0;
	start_cur = 0;
	quote = NO_QUOTE;
	while (s[end_cur] != '\0')
	{
		quote = get_quote_status(s[end_cur], quote);
		if (s[end_cur] == c && quote == NO_QUOTE)
			start_cur = end_cur + 1;
		if (s[end_cur] != c && (s[end_cur + 1] == c || s[end_cur + 1] == '\0')
			&& quote == NO_QUOTE)
		{
			while (s[start_cur] != '\0' && is_space(s[start_cur]))
				start_cur++;
			result[word] = malloc(sizeof(char) * (end_cur - start_cur + 2));
			if (!result[word])
			{
				while (--word >= 0)
					free(result[word]);
				return (0);
			}
			ft_strlcpy(result[word], (s + start_cur), end_cur - start_cur + 2);
			word++;
		}
		end_cur++;
	}
	result[word] = NULL;
	return (1);
}

char	**ft_split_cmd(char const *s, char c)
{
	char	**result;

	if (!s)
		return (0);
	result = malloc(sizeof(char *) * (numwords(s, c) + 1));
	if (!result)
		return (0);
	if (!split_words(result, s, c, 0))
		return (free(result), NULL);
	return (result);
}

void	init_node(t_cmd *new, t_env *list)
{
	new->token = NULL;
	new->env = list;
	new->args = NULL;
	new->arg_arr = NULL;
	new->file = NULL;
	new->path = NULL;
	new->next = NULL;
	new->fd_in = 0;
	new->fd_out = 0;
}

t_cmd	*init_new_node(char *arr, t_cmd *new, t_env *env)
{
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		free(arr);
		return (NULL);
	}
	init_node(new, env);
	new->args = ft_strdup(arr);
	if (new->args == NULL)
		return (NULL);
	return (new);
}

void	initialize_arguments(t_cmd **line, char **user, t_env *env)
{
	t_cmd	*new;
	int		i;

	new = NULL;
	i = 0;
	while (user[i])
	{
		new = init_new_node(user[i], new, env);
		if (new == NULL)
		{
			free(user[i]);
			return ;
		}
		free(user[i]);
		arg_add_back(line, new);
		i++;
	}
}

void add_back(t_cmd**stack, t_cmd*lst)
{
	
}

void	arg_add_back(t_cmd **stack, t_cmd *new)
{
	t_cmd	*current;

	current = *stack;
	if (stack)
	{
		if (*stack == NULL)
			*stack = new;
		else
		{
			current = arg_last(*(stack));
			current->next = new;
		}
		new = NULL;
	}
}

t_cmd	*arg_last(t_cmd *lst)
{
	t_cmd	*current;

	current = lst;
	if (lst == NULL)
		return (NULL);
	while (current->next != 0)
	{
		current = current->next;
	}
	return (current);
}
