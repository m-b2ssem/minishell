/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_blanks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/26 21:01:30 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 21:12:09 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str(t_token *to_delete)
{
	if (to_delete)
	{
		if (to_delete->string)
			free(to_delete->string);
		free(to_delete);
	}
}

static void	blanks_init(t_token **p, t_token **to, t_token **t, t_token **c)
{
	*p = NULL;
	*to = NULL;
	*t = NULL;
	*c = NULL;
}

void	remove_blank_tokens(t_cmd *cmd)
{
	t_token	*current;
	t_token	*prev;
	t_token	*to_delete;
	t_token	*tmp;

	blanks_init(&prev, &to_delete, &tmp, &current);
	current = cmd->token;
	while (current != NULL)
	{
		tmp = current->next;
		if (current->type == BLANK || current->type == NON)
		{
			to_delete = current;
			if (prev == NULL && current->next != NULL)
				cmd->token = current->next;
			else
				prev->next = current->next;
			free_str(to_delete);
		}
		else
			prev = current;
		current = tmp;
	}
}

void	remove_blank_tokens_from_cmds(t_cmd **cmd_list)
{
	t_cmd	*curr_cmd;

	curr_cmd = *cmd_list;
	while (curr_cmd != NULL)
	{
		remove_blank_tokens(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
}
