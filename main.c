/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:57:42 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:57:42 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

int	is_all_whitespace(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (!is_space((char)*str))
			return (0);
		str++;
	}
	return (1);
}

int	dd(t_cmd **cmd, t_env **env, int *status, char **envp)
{
	*cmd = NULL;
	*env = NULL;
	*status = 0;
	if (initialize_env_variables(env, envp) == NULL)
		return (1);
	return (0);
}

static int	handle_command(t_cmd **cmd, t_env **envp, int *status, char *str)
{
	if (is_all_whitespace(str))
		return (1);
	add_history(str);
	*status = parse_cmd(str, cmd, *envp, *status);
	if (*status)
		free_everything(cmd);
	else
	{
		*status = execute(cmd);
		free_everything(cmd);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	int		status;
	t_cmd	*cmd;
	t_env	*envp;

	if (!argc || !argv || dd(&cmd, &envp, &status, env))
		return (0);
	parent_signals();
	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
			return (free_list(&envp), 0);
		if (handle_command (&cmd, &envp, &status, str))
		{
			free(str);
			continue ;
		}
		free(str);
	}
	return (0);
}
