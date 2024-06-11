/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:54:02 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:54:02 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_valid_char_begin(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int	is_valid_char_rest(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	calculate_size(t_env *curr, char *org, char *tmp)
{
	int	res;
	int	diff;

	diff = 0;
	res = 0;
	if (!curr || !org || !tmp)
		return (res);
	if (ft_strlen(curr->value) >= ft_strlen(tmp))
		diff = ft_strlen(curr->value) - ft_strlen(tmp);
	else
		diff = ft_strlen(tmp) - ft_strlen(curr->value);
	res = ft_strlen(org) + diff;
	return (res);
}

int	calc_size_heredoc(char *value, char *org, char *tmp)
{
	int	res;
	int	diff;

	diff = 0;
	res = 0;
	if (!value || !org || !tmp)
		return (res);
	if (ft_strlen(value) >= ft_strlen(tmp))
		diff = ft_strlen(value) - ft_strlen(tmp);
	else
		diff = ft_strlen(tmp) - ft_strlen(value);
	res = ft_strlen(org) + diff;
	return (res);
}
