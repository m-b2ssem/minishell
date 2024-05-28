/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 00:49:19 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 14:55:20 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	token_add_back2(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (!*head)
		*head = new_token;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_token;
	}
}

t_token	*init_new_list(char **arr, t_token **head)
{
	t_token	*new;
	t_token	*tmp;
	int		i;

	new = NULL;
	i = -1;
	if (arr == NULL)
		return (NULL);
	while (arr[++i])
	{
		new = reinitialize_tokens(arr[i]);
		if (!new)
		{
			cleanup_on_error(head, arr, i);
			return (NULL);
		}
		token_add_back2(head, new);
	}
	free(arr);
	return (*head);
}

void	in_retok(t_token **c_t, t_token **l, t_token **nl, t_token **p)
{
	*c_t = NULL;
	*l = NULL;
	*nl = NULL;
	*p = NULL;
}

int	pre_check(char **arr, t_token *t)
{
	if (arr[0] && ft_strcmp(arr[0], t->string) == 0 && arr[1] == NULL)
	{
		free(arr[0]);
		free(arr);
		return (1);
	}
	return (0);
}

t_token	*return_prev(t_token *cur_th, t_token *tok, t_token *prev)
{
	while (cur_th && cur_th != tok)
	{
		prev = cur_th;
		cur_th = cur_th->next;
	}
	return (prev);
}
