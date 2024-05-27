/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_joining.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/05/26 17:55:43 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:55:43 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


char	*concatenate_strings(char *new, t_token **head)
{
	t_token *curr_tok;
	t_token *prev_tok;

	curr_tok = *head;
	prev_tok = NULL;
	while (curr_tok != NULL)
	{
		if (curr_tok->join == 1)
		{
			new = my_strcat(new, curr_tok->string);
			if (new == NULL)
				return (NULL);
			new = my_strcat(new, "");
		}
		else if (prev_tok != NULL && prev_tok->join == 1
			&& curr_tok->join == 0)
			break ;
		prev_tok = curr_tok;
		curr_tok = curr_tok->next;
	}
	return (new);
}

char	*join_strings(t_token **head)
{
	char		*new;
	int			total_len;
	t_token		*curr_tok;
	t_token		*prev_tok;

	curr_tok = *head;
	prev_tok = NULL;
	total_len = calculate_total_length(curr_tok, prev_tok);
	if (total_len == 0)
		return (NULL);
	new = ft_calloc(total_len + 1, sizeof(char));
	if (!new)
		return (NULL);
	new[0] = '\0';
	new = concatenate_strings(new, head);
	return (new);
}

int	assign_join_variable(t_cmd **cmd)
{
	t_cmd *curr_cmd;
	t_token *curr_tok;
	t_token *head_tok;
	int flag;

	flag = 0;
	curr_cmd = NULL;
	curr_tok = NULL;
	curr_cmd = *cmd;
	head_tok = curr_cmd->token;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		flag += loop_assign_join(curr_tok, head_tok);
		curr_cmd = curr_cmd->next;
	}
	return (flag);
}

int	find_node_and_modify(char *j, t_token *f, t_cmd **c)
{
	t_token *curr_tok;
	t_cmd *cur;
	int here;

	here = 0;
	cur = *c;
	curr_tok = cur->token;
	while (curr_tok != NULL)
	{
		if (curr_tok->type == HERE_DOC)
			here = 1;
		else if (curr_tok == f)
		{
			if (curr_tok->next != NULL)
			{
				if (j == NULL)
					return (1);
				if (j != curr_tok->string)
					set_to_type_arg(curr_tok, j, here);
				if (curr_tok->string == NULL)
					return (1);
			}
		}
		curr_tok = curr_tok->next;
	}
	return (0);
}

int	join_quoted_strings(t_cmd **head)
{
	char *new;
	t_token *first;
	t_cmd *curr_cmd;
	t_token *curr_tok;

	new = NULL;
	first = NULL;
	curr_tok = NULL;
	curr_cmd = *head;
	if (assign_join_variable(head) > 0)
	{
		while (curr_cmd != NULL)
		{
			curr_tok = curr_cmd->token;
			process_tok(&curr_cmd, &curr_tok, &new, &first);
			curr_cmd = curr_cmd->next;
		}
	}
	return (0);
}
