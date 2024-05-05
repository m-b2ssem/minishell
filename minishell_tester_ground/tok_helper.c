
#include "minishell.h"

void	init_node_tokens(t_token *new)
{
	new->string = NULL;
	new->expansion = 0;
	new->next = NULL;
	new->type = NON;
}

t_token	*new_token(char *arg, t_token **begin)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	init_node_tokens(new);
}
