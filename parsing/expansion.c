/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:54:48 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:54:48 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal;

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

int	remove_lone_dollars(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;
	int		flag;

	flag = 0;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_token = curr_cmd->token;
		while (curr_token != NULL)
		{
			if (curr_token->string != NULL && ft_strcmp(curr_token->string,
					"exit") == 0)
				flag = 1;
			else if (curr_token->string != NULL)
			{
				if (!flag && ft_strcmp(curr_token->string, "$") == 0
					&& curr_token->type == ARG)
					curr_token->type = BLANK;
			}
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

void	generate_args_for_tok(t_token *tok, t_token **last_new,
		t_token **new_list)
{
	char	*new;
	int		size;
	int		i;
	int		start;

	init_args_var(&i, &start, &new);
	size = ft_strlen(tok->string);
	while (i < size)
	{
		start = i;
		if (is_redirection(tok->string[i]))
			get_redirection(tok->string, &i);
		else if (is_space(tok->string[i]))
			i++;
		else
			get_args_other(tok->string, &i);
		new = ft_substr(tok->string, start, i - start);
		if (reinit(new, new_list, last_new) == 1)
		{
			free(new);
			break ;
		}
		if (i == start)
			break ;
	}
}
