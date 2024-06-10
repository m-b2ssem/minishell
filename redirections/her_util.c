/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:57:16 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 18:03:28 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*after_dollar(t_dollar_vars *v, char **ad, int *k)
{
	(*v->i)++;
	*ad = ft_calloc((ft_strlen(v->str) + 1), sizeof(char));
	if (!*ad)
		return (free(v->new_str), NULL);
	while (v->str[*v->i] != '\0' && v->str[*v->i] != ' ')
		(*ad)[(*k)++] = v->str[(*v->i)++];
	(*ad)[*k] = '\0';
	return (*ad);
}

char	*process_dollar(t_dollar_vars *vars)
{
	char	*after_doller;
	char	*var_value;
	int		k;

	k = 0;
	after_doller = after_dollar(vars, &after_doller, &k);
	if (!after_doller)
		return (NULL);
	var_value = my_getenv(after_doller, vars->env);
	if (var_value && vars->tok->expansion == 0)
	{
		ft_strcpy(&vars->new_str[*vars->j], var_value);
		*vars->j += ft_strlen(var_value) ;
	}
	else
	{
		vars->new_str[(*vars->j)++] = '$';
		ft_strcpy(&vars->new_str[*vars->j], after_doller);
		*vars->j += k;
	}
	free(after_doller);
	return (vars->new_str);
}

char	*handle_doller(t_dollar_vars *vars)
{
	vars->new_str = process_dollar(vars);
	if (!vars->new_str)
		return (NULL);
	return (vars->new_str);
}

char	*my_getenv(char *name, t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = ft_strlen(name);
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->name, name, len) == 0 && tmp->export == 1)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
