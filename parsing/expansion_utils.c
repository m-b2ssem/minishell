#include "../minishell.h"

void	init_vars(int *i, t_token **prev, t_token **new_list,
		t_token **last_new)
{
	*i = 0;
	*prev = NULL;
	*new_list = NULL;
	*last_new = NULL;
}

void	init_retok_vars(t_cmd **line, t_token *tok, t_token **curr)
{
	*curr = (*line)->token;
	if (*curr == tok)
		(*line)->token = NULL;
	if (!tok || !tok->string)
		return ;
}

void	retokenizing_of_env_values(t_cmd **line, t_token *tok)
{
	t_token	*last_new;
	t_token	*new_list;
	t_token	*curr;
	t_token	*prev;
	int		i;

	initialize_retokenizing_variables(line, tok, &curr);
	init_vars(&i, &prev, &new_list, &last_new);
	if (curr == tok)
		(*line)->token = NULL;
	else
	{
		while (curr && curr != tok)
		{
			prev = curr;
			curr = curr->next;
		}
	}
	generate_args_for_tok(tok, &last_new, &new_list);
	update_token_links(line, prev, new_list);
	while (last_new && last_new->next)
		last_new = last_new->next;
	if (last_new)
		last_new->next = curr->next;
}

void	update_token_links(t_cmd **line, t_token *prev, t_token *new_list)
{
	if (prev)
		prev->next = new_list;
	else
		(*line)->token = new_list;
}

int	handle_expansion(t_cmd **line, int status)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;

	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		handle_expansion_loop(line, curr_tok, status);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
