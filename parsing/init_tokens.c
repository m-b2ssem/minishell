
#include "../minishell.h"

t_token	*token_last(t_token *lst)
{
	t_token	*current;

	current = lst;
	if (lst == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	token_add_back(t_token **begin, t_token *new)
{
	t_token	*token;

	token = *begin;
	if (begin)
	{
		if (*begin == NULL)
			*begin = new;
		else
		{
			token = token_last((*begin));
			token->next = new;
		}
		new = NULL;
	}
}

void	init_node_tokens(t_token *new)
{
	new->string = NULL;
	new->join = 0;
	new->expansion = 0;
	new->next = NULL;
	new->type = NON;
}

t_token	*new_token(char *arg, t_token *new)
{
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	init_node_tokens(new);
	new->string = ft_strdup(arg);
	if (new->string == NULL)
		return (NULL);
	return (new);
}

int	initialize_tokens(char *arg, t_token **type)
{
	t_token	*new;

	new = NULL;
	new = new_token(arg, new);
	if (new == NULL)
	{
		free(arg);
		return (1);
	}
	token_add_back(type, new);
	free(arg);
	return (0);
}
