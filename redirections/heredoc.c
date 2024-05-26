/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:57:24 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:57:24 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern sig_atomic_t	g_signal;

int	random_char(void)
{
	char	tmp[4];
	int		c;
	int		fd;

	fd = open("/dev/urandom", O_RDONLY);
	c = 0;
	if (fd == -1)
		return (-1);
	if (read(fd, tmp, 4) != 4)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	c = *((int *)tmp);
	if (c < 0)
		c = -c;
	c = c % 52;
	if (c < 26)
		return ('a' + c);
	else
		return ('A' + c - 26);
}

char	*random_name(void)
{
	char	*file;
	int		i;
	int		c;

	i = 0;
	c = 0;
	file = malloc(sizeof(char) * 31);
	if (!file)
		return (NULL);
	while (i < 30)
	{
		c = random_char();
		if (c == -1)
		{
			free(file);
			return (NULL);
		}
		file[i] = c;
		i++;
	}
	file[30] = '\0';
	return (file);
}

char	*check_for_env_value(char *str, t_env *env, t_token *tok)
{
	t_dollar_vars	vars;
	int				i;
	int				j;

	i = 0;
	j = 0;
	vars.str = str;
	vars.env = env;
	vars.tok = tok;
	vars.i = &i;
	vars.j = &j;
	vars.new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!vars.new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != '$')
			vars.new_str[j++] = str[i++];
		else
			if (!handle_doller(&vars))
				return (NULL);
	}
	vars.new_str[j] = '\0';
	return (free(str), vars.new_str);
}

int	write_inside_file(t_cmd *cmd, char *word, int fd, t_token *tok)
{
	char	*str;

	str = NULL;
	while (1)
	{
		str = readline(">");
		if (str == NULL || g_signal == 130)
		{
			g_signal = 0;
			return (-1);
		}
		if (strcmp_custom(word, str) == 0)
			break ;
		if (str != NULL)
		{
			str = check_for_env_value(str, cmd->env, tok);
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
	free(str);
	return (0);
}

int	heredoc(t_cmd *cmd, char *word, t_token *tok)
{
	int		fd;
	char	*file;

	file = random_name();
	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_RDWR, 0644);
	if (fd == -1)
		return (free(file), -1);
	heredoc_signals();
	write_inside_file(cmd, word, fd, tok);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (free(file), -1);
	cmd->fd_in = fd;
	cmd->file = file;
	return (fd);
}
