/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_joining_util_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:55:32 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:55:33 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_to_type_arg(t_token *curr_tok, char *join, int here)
{
	free(curr_tok->string);
	curr_tok->string = join;
	curr_tok->join = 0;
	curr_tok->type = ARG;
	if (here)
		curr_tok->expansion = 1;
	here = 0;
}

int	loop_assign_join(t_token *curr_tok, t_token *head_tok)
{
	t_token	*prev_tok;
	int		flag;

	prev_tok = NULL;
	flag = 0;
	while (curr_tok != NULL)
	{
		if (prev_tok != NULL && !join_redir_helper(prev_tok)
			&& curr_tok->string != NULL && join_quoted_helper(curr_tok))
		{
			if (join_quoted_helper(prev_tok) || (prev_tok->type == BUILTIN
					&& prev_tok != head_tok))
				prev_tok->join = 1;
			curr_tok->join = 1;
			flag++;
		}
		prev_tok = curr_tok;
		curr_tok = curr_tok->next;
	}
	return (flag);
}

int	calculate_total_length(t_token *curr_tok, t_token *prev_tok)
{
	int	total_len;

	total_len = 0;
	while (curr_tok != NULL)
	{
		if (curr_tok->join == 1)
			total_len += (ft_strlen(curr_tok->string)) + 1;
		else if (curr_tok->join == 0 && curr_tok->type == BLANK
			&& prev_tok->join == 1 && prev_tok != NULL)
			break ;
		prev_tok = curr_tok;
		curr_tok = curr_tok->next;
	}
	return (total_len);
}
