/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:45:04 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:45:04 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_env *temp)
{
	while (temp != NULL)
	{
		if (temp->export == 1)
		{
			printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		}
		else if (temp->export == 0)
		{
			printf("declare -x %s\n", temp->name);
		}
		temp = temp->next;
	}
}

void	update_value(t_cmd *cmd, char *name, char *value, int export)
{
	t_env	*temp;

	temp = cmd->env;
	while (temp != NULL)
	{
		if (strcmp_custom(temp->name, name) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			temp->export = export;
			break ;
		}
		temp = temp->next;
	}
}

void	return_name(char *arg, char **name)
{
	int	i;

	i = 0;
	while (arg[i] != '=' && arg[i] != '\0')
	{
		(*name)[i] = arg[i];
		i++;
	}
	(*name)[i] = '\0';
}

int	search_if_variable_exist(t_cmd *cmd, char *name)
{
	t_env	*temp;

	temp = cmd->env;
	while (temp != NULL)
	{
		if (strcmp_custom(temp->name, name) == 0)
		{
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	swap(t_env *a, t_env *b)
{
	char	*temp_name;
	char	*temp_value;
	int		temp_export;

	temp_name = ft_strdup(a->name);
	temp_value = ft_strdup(a->value);
	temp_export = a->export;
	free(a->name);
	free(a->value);
	a->name = ft_strdup(b->name);
	a->value = ft_strdup(b->value);
	a->export = b->export;
	free(b->name);
	free(b->value);
	b->name = temp_name;
	b->value = temp_value;
	b->export = temp_export;
}
