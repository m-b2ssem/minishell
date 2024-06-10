/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_array_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:53:46 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:53:46 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_array(t_cmd *cmd, t_token *tok, int *i, int *option)
{
	if (tok->type == BUILTIN || tok->type == ARG || tok->type == D_QUOTE
		|| tok->type == S_QUOTE)
	{
		cmd->arg_arr[(*i)++] = tok->string;
		*option = 0;
	}
	else if (tok->type == OPTION && !(*option))
	{
		*option = 1;
		cmd->arg_arr[(*i)++] = tok->string;
	}
}

void	initialize_arg_array(t_cmd *cmd)
{
	int		i;
	t_token	*tok;
	int option;

	tok = cmd->token;
	i = 0;
	option = 0;
	while (tok != NULL)
	{
		while (tok != NULL && tok->type == BLANK)
			tok = tok->next;
		while (tok != NULL)
		{
			init_array(cmd, tok, &i, &option);
			tok = tok->next;
		}
	}
	cmd->arg_arr[i] = NULL;
}

int	count_arg(t_cmd *cmd)
{
	t_token	*tok;
	int		size;

	size = 0;
	tok = cmd->token;
	while (tok != NULL)
	{
		if (tok->type == ARG || tok->type == BUILTIN || tok->type == D_QUOTE
			|| tok->type == S_QUOTE || tok->type == OPTION)
			size++;
		tok = tok->next;
	}
	return (size);
}

int	create_arr_for_exec(t_cmd **line)
{
	t_cmd	*curr_cmd;
	char	**arg_arr;
	int		size;

	size = 0;
	curr_cmd = NULL;
	arg_arr = NULL;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		size = count_arg(curr_cmd);
		arg_arr = ft_calloc((size + 1), sizeof(char *));
		if (!arg_arr)
			return (1);
		curr_cmd->arg_arr = arg_arr;
		initialize_arg_array(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
