/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_joining_util_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 02:09:22 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 02:09:22 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_join(t_token **t, char **n, t_token *f, t_cmd **c)
{
	if (f == NULL)
		return ;
	*n = join_strings(t);
	if (*n)
	{
		find_node_and_modify(*n, f, c);
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
	if (tok == NULL || *tok == NULL)
		return ;
	while (*tok != NULL)
	{
		while (*tok != NULL && (*tok)->join != 1)
			*tok = (*tok)->next;
		if (!process_n_token(*tok, cmd))
			break ;
		if (*tok == NULL)
			break ;
		*f = *tok;
		process_join(tok, n, *f, cmd);
		*tok = (*f)->next;
	}
}
