/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:54:15 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 03:00:40 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal;

char	*create_expansion(t_env *curr, char *org, int start, char *tmp)
{
	int		new_size;
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded = NULL;
	new_size = calculate_size(curr, org, tmp);
	if (new_size == 0)
		return (NULL);
	expanded = malloc(sizeof(char) * (new_size + 1));
	if (!expanded)
		return (NULL);
	while (i < (start - 1))
		expanded[j++] = org[i++];
	i = 0;
	while (curr->value[i])
		expanded[j++] = curr->value[i++];
	start += ft_strlen(tmp);
	while (org[start])
		expanded[j++] = org[start++];
	expanded[j] = '\0';
	return (expanded);
}

static void	exit_free(char *s, char *t)
{
	free(s);
	free(t);
}

static void	copy_strings(char *expand, t_token *tok, char *s, int start)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < (start - 1))
		expand[j++] = tok->string[i++];
	i = 0;
	while (s[i])
		expand[j++] = s[i++];
	while (tok->string[++start])
		expand[j++] = tok->string[start];
	expand[j] = '\0';
}

void	init(char **tmp, char **expand)
{
	*expand = NULL;
	*tmp = NULL;
}

char	*expand_exit_status(t_token *tok, int start, int status)
{
	char	*expand;
	char	*t;
	char	*s;

	expand = NULL;
	s = ft_itoa(status + g_signal);
	if (s == NULL)
		return (NULL);
	g_signal = 0;
	t = ft_itoa(status);
	if (t == NULL)
		return (free(s), NULL);
	expand = ft_calloc((ft_strlen(tok->string) + ft_strlen(t) + 1),
			sizeof(char));
	if (!expand)
		return (exit_free(s, t), NULL);
	copy_strings(expand, tok, s, start);
	exit_free(s, t);
	return (expand);
}
