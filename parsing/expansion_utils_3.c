/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:54:23 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/27 15:33:09 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	initi_poss_var(int *i, int *st, int *siz, t_token *tok)
{
	if (!tok || !tok->string)
		return (1);
	*i = 0;
	*st = 0;
	*siz = ft_strlen(tok->string);
	if (siz == 0)
		return (1);
	return (0);
}

void	helper(t_token *tok, char **expand, int *size, int *i)
{
	free(tok->string);
	tok->string = *expand;
	*size = ft_strlen(tok->string);
	*i = 0;
}

void	init(char **tmp, char **expand)
{
	*expand = NULL;
	*tmp = NULL;
}

char	*get_tmp_name(t_token *tok, int *i, int *start_name)
{
	int	size;

	size = ft_strlen(tok->string);
	while (*i < size)
	{
		while (tok->string[*i] && tok->string[*i] != '$')
			(*i)++;
		if (tok->string[*i] != '$')
			return (NULL);
		while (tok->string[*i] == '$')
			(*i)++;
		*start_name = *i;
		if (!is_valid_char_begin(tok->string[*start_name]))
			return (NULL);
		while (tok->string[*i] && tok->string[*i] != '$'
			&& is_valid_char_rest(tok->string[*i]))
			(*i)++;
		return (ft_substr(tok->string, *start_name, *i - *start_name));
	}
	return (NULL);
}

void	possible_expansion(t_cmd **cmd, t_token *tok, int status)
{
	int		i;
	int		start_name;
	int		size;
	char	*tmp_name;
	char	*expand;

	i = 0;
	size = ft_strlen(tok->string);
	if (initi_poss_var(&i, &start_name, &size, tok))
		return ;
	init(&tmp_name, &expand);
	while (i < size)
	{
		tmp_name = get_tmp_name(tok, &i, &start_name);
		if (tmp_name)
		{
			if (ft_strcmp(tmp_name, "?") == 0)
				expand = expand_exit_status(tok, start_name, status);
			else
				expand = get_env_value(tmp_name, tok, &(*cmd)->env, start_name);
			if (expand[0] != '\0')
				helper(tok, &expand, &size, &i);
			free(tmp_name);
		}
	}
}
