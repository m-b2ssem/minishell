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
/*   Created: 2024/05/26 17:54:41 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 19:58:03 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_token	*init_new_list(char **arr)
{
	t_token *new = NULL;
	t_token *head = NULL;
	t_token *tmp;
	t_token *current;
	int i = -1;

	if (arr == NULL)
		return (NULL);
	while (arr[++i])
	{
		new = reinitialize_tokens(arr[i]);
		if (!new)
		{
			while (head)
			{
				tmp = head;
				head = head->next;
				free(tmp->string);
				free(tmp);
			}
			while (arr[i])
				free(arr[--i]);
			free(arr);
			return (NULL);
		}
		free(arr[i]);
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
	}
	return (head);
}

void	retokenizing_of_env_values(t_cmd **line, t_token *tok)
{
	t_token *curr_tok_head;
	t_token *start;
	t_token *new_list;
	char **arr = NULL;
	curr_tok_head = (*line)->token;
	if (!tok || !tok->string)
		return ;
	arr = ft_split(tok->string, ' ');
	if (arr == NULL)
		return ;
	if (arr[0] && ft_strcmp(arr[0], tok->string) == 0 && arr[1] == NULL)
	{
		free(arr[0]);
		free(arr);
		return ;
	}
	if (curr_tok_head == tok)
		start = curr_tok_head;
	else
	{
		while (curr_tok_head && curr_tok_head != tok)
		{
			start = curr_tok_head;
			curr_tok_head = curr_tok_head->next;
		}
	}
	new_list = init_new_list(arr);
	if (!new_list)
		return ;
	if (start == (*line)->token)
	{
		new_list->next = curr_tok_head->next;
		(*line)->token = new_list;
	}
	else
	{
		t_token *prev = start;
		t_token *current = new_list;
		while (current->next)
			current = current->next;
		current->next = curr_tok_head->next;
		prev->next = new_list;
	}
	free(tok->string);
	free(tok);
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

int	handle_expansion(t_cmd **line, int status)
{
	t_cmd *curr_cmd;
	t_token *curr_tok;

	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		hand_exp_loop(line, curr_tok, status);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
