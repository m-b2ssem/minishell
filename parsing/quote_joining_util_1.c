#include "../minishell.h"

void	process_join(t_token **tok, char **new, t_token *f)
{
	*new = join_strings(tok);
	if (*new)
	{
		find_node_and_modify(*new, tok, f);
		find_and_modify_unused_nodes(f);
	}
}

bool	process_n_token(t_token *curr_tok, t_cmd **curr_cmd)
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

void	process_tok(t_cmd **cmd, t_token **tok, char **n, t_token **f)
{
	while (*tok != NULL)
	{
		while (*tok != NULL && (*tok)->join != 1)
			*tok = (*tok)->next;
		if (!process_n_token(*tok, cmd))
			break ;
		*f = *tok;
		process_join(tok, n, *f);
		*tok = (*f)->next;
	}
}
