/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 03:32:50 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 03:32:50 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_list(t_cmd **head)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = *head;
	while (cmd != NULL)
	{
		printf("Node: %s\n", cmd->args);
		tok = cmd->token;
		while (tok != NULL)
		{
			printf("\tTOK:-%s-\n", tok->string);
			printf("\tTYPE: %d\n", tok->type);
			printf("\tJOIN: %d\n", tok->join);
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}

int	parse_cmd_2(t_cmd **line, int status)
{
	handle_expansion(line, status);
	if (remove_lone_dollars(line) != 0)
		return (1);
	join_quoted_strings(line);
	if (redirection_usage(line) != 0)
		return (ft_putstr_fd(REDIR, 2), 1);
	echo_option_checker(line);
	remove_blank_tokens_from_cmds(line);
	if (create_arr_for_exec(line) != 0)
		return (1);
	return (0);
}

int	decide_token_type(t_cmd **line)
{
	t_cmd	*curr;
	t_token	*tok;

	if (line == NULL)
		return (1);
	curr = *line;
	while (curr != NULL)
	{
		tok = curr->token;
		while (tok != NULL)
		{
			token_type(tok);
			tok = tok->next;
		}
		curr = curr->next;
	}
	return (0);
}

int	parse_cmd(char *str, t_cmd **line, t_env *env, int status)
{
	char	**arr;

	arr = NULL;
	if (first_string_checks(str) == 1)
		return (1);
	arr = ft_split_cmd(str, '|');
	if (arr == NULL || arr[0] == NULL)
	{
		if (arr)
			free(arr);
		return (1);
	}
	if (initialize_arguments(line, arr, env) != 0)
		return (free_everything(line), 1);
	if (iterate_through_cmd_args(line) != 0)
		return (free_everything(line), 1);
	decide_token_type(line);
	if (redirection_spell_check(line) == 1)
		return (ft_putstr_fd(REDIR, 2), 1);
	if (search_quotes_modify(line))
		return (free_everything(line), 1);
	if (parse_cmd_2(line, status))
		return (free_everything(line), 1);
	return (0);
}

void	handle_expansion_edgecase(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	t_token	*prev;
	int		here;

	here = 0;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		prev = NULL;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->type == HERE_DOC)
				here = 1;
			else if (here && curr_tok->string != NULL
				&& (curr_tok->type == S_QUOTE || curr_tok->type == D_QUOTE)
				&& prev != NULL && prev->type == ARG)
				prev->type = curr_tok->type;
			prev = curr_tok;
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
