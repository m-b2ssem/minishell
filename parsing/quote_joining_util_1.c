#include "../minishell.h"

void	process_joined_strings(t_token **curr_tok, char **new, t_token *first)
{
	*new = join_strings(curr_tok);
	if (*new)
	{
		find_node_and_modify(*new, curr_tok, first);
		find_and_modify_unused_nodes(first);
	}
}

bool	process_null_token_nor(t_token *curr_tok, t_cmd **curr_cmd)
{
	if (curr_tok == NULL)
	{
		if ((*curr_cmd)->next != NULL)
		{
			*curr_cmd = (*curr_cmd)->next;
			return (true);
		}
		else
			return (false);
	}
	return (true);
}

void	process_tokens_nor(t_cmd **curr_cmd, t_token **curr_tok,
		char **new, t_token **first)
{
	while (*curr_tok != NULL)
	{
		while (*curr_tok != NULL && (*curr_tok)->join != 1)
			*curr_tok = (*curr_tok)->next;
		if (!process_null_token_nor(*curr_tok, curr_cmd))
			break ;
		*first = *curr_tok;
		process_joined_strings(curr_tok, new, *first);
		*curr_tok = (*first)->next;
	}
}
