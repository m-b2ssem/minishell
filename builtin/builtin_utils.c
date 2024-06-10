/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 11:43:13 by amirfatt          #+#    #+#             */
/*   Updated: 2024/06/10 12:33:21 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_value(char *arg, int *i, int *export)
{
	if (arg[(*i)] == '=')
	{
		*export = 1;
		(*i)++;
	}
}

int	create_add_new_variable(t_cmd *cmd, int export, char *name, char *value)
{
	t_env	*new;

	new = NULL;
	new = lst_new(name, value, new, export);
	if (!new)
		return (free(name), free(value), 1);
	lst_addback(&cmd->env, new);
	return (0);
}
