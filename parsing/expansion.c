/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 02:06:29 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 02:06:29 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *t, t_token *tok, t_env **lst, int s)
{
	t_env	*curr;
	char	*org_str;

	org_str = tok->string;
	curr = NULL;
	if (t == NULL)
		return (NULL);
	curr = find_accord_env_name(t, lst);
	if (curr == NULL)
		return (forbidden_variable_name(tok, t, s));
	return (create_expansion(curr, org_str, s, t));
}

void	process_tokenn(t_token *token, int *flag)
{
	if (token->string != NULL && ft_strcmp(token->string, "exit") == 0)
		*flag = 1;
	else if (token->string != NULL && !*flag
		&& ft_strcmp(token->string, "$") == 0 && token->type == ARG)
		token->type = BLANK;
}

int	remove_lone_dollars(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;
	int		flag;

	flag = 0;
	if (line == NULL || *line == NULL)
		return (1);
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_token = curr_cmd->token;
		while (curr_token != NULL)
		{
			process_tokenn(curr_token, &flag);
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
