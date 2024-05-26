/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_helper_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:56:49 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:56:49 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_other_separator(char c)
{
	if (c == ' ' || c == '	' || c == '<' || c == '>' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
	{
		if (c == '\t')
			c = ' ';
		return (1);
	}
	return (0);
}

int	find_char(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}
