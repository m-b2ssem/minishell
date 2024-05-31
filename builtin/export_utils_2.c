/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:44:31 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:44:54 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	alloc_mem(char **name, char **value, const char *arg)
{
	*name = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!*name)
		return (1);
	*value = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!*value)
	{
		free(*name);
		return (1);
	}
	return (0);
}
