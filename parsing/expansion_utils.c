/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:54:41 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 19:58:03 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	init_retok_vars(line, tok, &curr);
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
	update_links(line, prev, new_list);
	while (last_new && last_new->next)
		last_new = last_new->next;
	if (last_new && last_new->next != NULL)
		last_new->next = curr->next;
}

void	update_links(t_cmd **l, t_token *p, t_token *n_lst)
{
	if (p)
		p->next = n_lst;
	else
		(*l)->token = n_lst;
}

int	handle_expansion(t_cmd **line, int status)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;

	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		hand_exp_loop(line, curr_tok, status);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
