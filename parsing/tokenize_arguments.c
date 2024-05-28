/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:31:16 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 03:31:16 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_token(t_token_vars *vars)
{
	vars->start = vars->i;
	if (is_redirection(vars->curr->args[vars->i]) && vars->stat == NO_QUOTE)
		get_redirection(vars->curr->args, &vars->i);
	else if (is_quotes((vars->curr->args[vars->i])))
	{
		get_string_in_quotes(vars->curr->args, &vars->i);
		++vars->i;
	}
	else if (is_space(vars->curr->args[vars->i]))
		vars->i++;
	else
		get_arguments(vars->curr->args, &vars->i);
	vars->arg = ft_substr(vars->curr->args, vars->start, vars->i
			- vars->start);
}

int	split_into_tokens(t_cmd **line)
{
	t_token_vars	vars;

	vars.arg = NULL;
	vars.curr = *line;
	vars.size = ft_strlen(vars.curr->args);
	if (vars.size == 0)
		return (1);
	vars.stat = NO_QUOTE;
	vars.start = 0;
	vars.i = 0;
	while (vars.i < vars.size)
	{
		process_token(&vars);
		if (initialize_tokens(vars.arg, (&vars.curr->token)) == 1)
			return (1);
	}
	return (0);
}

int	iterate_through_cmd_args(t_cmd **line)
{
	t_cmd	*current;

	current = *line;
	while (current != NULL)
	{
		if (split_into_tokens(&current) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}
