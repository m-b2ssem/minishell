/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:44:22 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:44:22 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	free_variable(t_env *curr)
{
	free(curr->name);
	free(curr->value);
	free(curr);
}

int	builtin_unset(t_env **head, t_cmd *cmd)
{
	t_env	*prev;
	t_env	*curr;
	t_env	*tmp;
	int		i;

	i = 0;
	while (cmd->arg_arr[i] != NULL)
	{
		prev = NULL;
		curr = *head;
		while (curr != NULL)
		{
			if (ft_strcmp(curr->name, cmd->arg_arr[i]) == 0)
			{
				if (prev == NULL)
					*head = curr->next;
				else
					prev->next = curr->next;
				tmp = curr;
				curr = curr->next;
				free_variable(tmp);
			}
			else
			{
				prev = curr;
				curr = curr->next;
			}
		}
		i++;
	}
	return (0);
}
