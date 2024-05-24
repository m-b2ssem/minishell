#include "../minishell.h"

int	join_redir_helper(t_token *token)
{
	if (token->type == BLANK || token->type == REDIR_IN
		|| token->type == REDIR_OUT || token->type == APPEND
		|| token->type == HERE_DOC)
		return (1);
	return (0);
}

int	join_quoted_helper(t_token *curr_tok)
{
	if (curr_tok->type == D_QUOTE || curr_tok->type == S_QUOTE
		|| curr_tok->type == ARG)
		return (1);
	return (0);
}

int	find_and_modify_unused_nodes(t_token *tok)
{
	t_token	*tmp;

	tmp = tok;
	if (tmp == NULL)
		return (1);
	if (tmp->next != NULL && join_quoted_helper(tmp))
	{
		tmp = tmp->next;
		while (tmp != NULL && tmp->join == 1)
		{
			if (tmp->type != BLANK && tmp->join == 1)
			{
				tmp->type = NON;
				tmp->join = 0;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
