/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/28 00:48:18 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 00:48:18 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_token_links(t_cmd **l, t_token *p, t_token *nl, t_token *t)
{
	t_token	*last_new;

	last_new = nl;
	if (p)
		p->next = nl;
	else
		(*l)->token = nl;
	while (last_new && last_new->next)
		last_new = last_new->next;
	if (t->next != NULL)
		last_new->next = t->next;
	else
		last_new->next = NULL;
}

void	retokenizing_of_env_values(t_cmd **line, t_token *tok)
{
	t_token	*curr_tok_head;
	t_token	*last_new;
	t_token	*new_list;
	t_token	*prev;
	char	**arr;

	arr = NULL;
	if (!line || !tok || !tok->string)
		return ;
	in_retok(&curr_tok_head, &last_new, &new_list, &prev);
	curr_tok_head = (*line)->token;
	arr = ft_split(tok->string, ' ');
	if (arr == NULL || pre_check(arr, tok) == 1)
		return ;
	prev = return_prev(curr_tok_head, tok, prev);
	new_list = init_new_list(arr, &new_list);
	update_token_links(line, prev, new_list, tok);
	free(tok->string);
	tok->string = NULL;
}

int	handle_expansion(t_cmd **line, int status)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;

	if (line == NULL || *line == NULL)
		return (1);
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		hand_exp_loop(line, curr_tok, status);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
