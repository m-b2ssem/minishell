/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:45:21 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:45:21 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*lst_last(t_env *lst)
{
	t_env	*current;

	current = lst;
	if (lst == 0)
		return (0);
	while (current->next != 0)
		current = current->next;
	return (current);
}

t_env	*lst_new(char *name, char *value, t_env *new, int export)
{
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	if (!new->name || !new->value)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->export = export;
	new->next = NULL;
	return (new);
}

void	lst_addback(t_env **list, t_env *new)
{
	t_env	*current;

	if (list)
	{
		if (*list == NULL)
			*list = new;
		else
		{
			current = lst_last(*(list));
			current->next = new;
		}
		new = NULL;
	}
}

static char	*get_env_value_new(const char *name)
{
	char	*value;
	char	*tmp;

	if (ft_strcmp(name, "SHLVL") == 0)
	{
		value = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	}
	else
	{
		tmp = getenv(name);
		if (tmp)
			value = ft_strdup(tmp);
		else
			value = ft_strdup("");
	}
	return (value);
}

t_env	*initialize_env_variables(t_env **head, char **env)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*new;

	i = -1;
	while (env[++i] != NULL)
	{
		name = ft_substr(env[i], 0, find_char(env[i]));
		value = get_env_value_new(name);
		new = lst_new(name, value, new, 1);
		if (new == NULL)
		{
			free_n_v(name, value);
			free_env_list(*head);
			return (NULL);
		}
		lst_addback(head, new);
		free_n_v(name, value);
	}
	return (*head);
}
