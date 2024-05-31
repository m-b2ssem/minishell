/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 02:05:35 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 02:05:35 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_checks(t_token *tok, char **new)
{
	*new = NULL;
	if (tok == NULL || tok->string == NULL)
		return (1);
	if (ft_strcmp(tok->string, "''") == 0 || ft_strcmp(tok->string,
			"\"\"") == 0)
		tok->string[0] = '\0';
	return (0);
}

int	update_quote_strings(t_token *tok)
{
	char	*s1;
	char	*s2;
	char	*new;

	s1 = "\"";
	s2 = "\'";
	if (quote_checks(tok, &new) != 0)
		return (1);
	if (tok->string[0] == '"')
		new = ft_strtrim(tok->string, s1);
	else if (tok->string[0] == '\'')
		new = ft_strtrim(tok->string, s2);
	if (new == NULL)
		return (1);
	if (new != tok->string)
	{
		free(tok->string);
		tok->string = new;
		if (tok->string == NULL)
			return (1);
	}
	return (0);
}

int	search_quotes_modify(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;

	if (line == NULL || *line == NULL)
		return (1);
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->string[0] != '\0')
			{
				if (curr_tok->type == D_QUOTE || curr_tok->type == S_QUOTE)
					update_quote_strings(curr_tok);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
