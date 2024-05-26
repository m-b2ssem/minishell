/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:56:41 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:56:41 by amirfatt         ###   ########.fr       */
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
	vars->arg = ft_substr(vars->curr->args, vars->start, vars->i - vars->start);
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

/*int	split_into_tokens(t_cmd **line)
{
	char			*arg;
	int				size;
	t_quote_status	stat;
	t_cmd			*curr;
	int				start;
	int				i;

	arg = NULL;
	curr = *line;
	size = ft_strlen(curr->args);
	if (size == 0)
		return (1);
	stat = NO_QUOTE;
	start = 0;
	i = 0;
	while (i < size)
	{
		start = i;
		if (is_redirection(curr->args[i]) && stat == NO_QUOTE)
			get_redirection(curr->args, &i);
		else if (is_quotes((curr->args[i])))
		{
			get_string_in_quotes(curr->args, &i);
			++i;
		}
		else if (is_space(curr->args[i]))
			i++;
		else
			get_arguments(curr->args, &i);
		arg = ft_substr(curr->args, start, i - start);
		if (initialize_tokens(arg, (&curr->token)) == 1)
			return (1);
	}
	return (0);
}*/

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
