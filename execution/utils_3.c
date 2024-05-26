/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:46:24 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:46:24 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close_fd(t_cmd *cmd)
{
	t_cmd	*cur;

	cur = cmd;
	while (cur)
	{
		if (cur->fd_in != 0)
			close(cur->fd_in);
		if (cur->fd_out != 1)
			close(cur->fd_out);
		cur = cur->next;
	}
	return (0);
}

int	env_len(t_env *env)
{
	int		len;
	t_env	*tmp;

	len = 0;
	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->export == 1)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_to_char(t_env *env)
{
	t_env	*tmp;
	char	**new_env;
	int		i;

	tmp = env;
	i = env_len(tmp);
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->export == 1)
		{
			new_env[i] = ft_strjoin(tmp->name, "=");
			new_env[i] = ft_strjoin(new_env[i], tmp->value);
		}
		else
			new_env[i] = ft_strjoin(tmp->name, "=");
		i++;
		tmp = tmp->next;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	custom_exe(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id)
{
	int	status;

	status = 0;
	if (ft_strcmp("pwd", cmd->arg_arr[0]) == 0)
		status = builtin_pwd();
	if (ft_strcmp("cd", cmd->arg_arr[0]) == 0)
		status = builtin_cd(cmd);
	if (ft_strcmp("echo", cmd->arg_arr[0]) == 0)
		status = builtin_echo(cmd);
	if (ft_strcmp("export", cmd->arg_arr[0]) == 0)
		status = builtin_export(cmd);
	if (ft_strcmp("env", cmd->arg_arr[0]) == 0)
		status = builtin_env(cmd->env, cmd);
	if (ft_strcmp("unset", cmd->arg_arr[0]) == 0)
		status = builtin_unset(&cmd->env, cmd);
	if (ft_strcmp("exit", cmd->arg_arr[0]) == 0)
		status = builtin_exit(cmd, tmp, pross_id);
	return (status);
}

int	one_operation(t_cmd *cmd, t_cmd *tmp, pid_t *pross_ids)
{
	int	status;

	status = 0;
	status = custom_exe(cmd, tmp, pross_ids);
	close_fd(tmp);
	free(pross_ids);
	return (status);
}
