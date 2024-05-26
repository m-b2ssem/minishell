/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:46:14 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:46:14 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_exit(t_cmd *tmp, pid_t *pross_id, int status)
{
	free_cmd(tmp);
	free(pross_id);
	exit(status);
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd != NULL)
	{
		if (cmd->arg_arr)
			free(cmd->arg_arr);
		if (cmd->token)
			free_list_tokens(&cmd->token);
		if (cmd->args)
			free(cmd->args);
		if (cmd->file)
			free(cmd->file);
		if (cmd->path)
			free(cmd->path);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

int	last_exit_status(int *exit_statuses, int len)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < len)
	{
		if (i == len - 1)
		{
			status = exit_statuses[i];
			break ;
		}
		i++;
	}
	return (status);
}

int	wait_pid(pid_t *pross_id, int len)
{
	int	i;
	int	*exit_statuses;
	int	exit_status;
	int	status;

	i = 0;
	status = 0;
	exit_statuses = malloc(sizeof(int) * len);
	if (!exit_statuses)
		return (-1);
	while (i < len)
	{
		waitpid(pross_id[i], &exit_status, 0);
		if (WIFSIGNALED(exit_status))
		{
			exit_statuses[i] = 128 + WEXITSTATUS(exit_status);
		}
		else if (WIFEXITED(exit_status))
		{
			exit_statuses[i] = WEXITSTATUS(exit_status);
		}
		i++;
	}
	status = last_exit_status(exit_statuses, len);
	return (free(exit_statuses), status);
}

int	builtin(t_cmd *cmd)
{
	if (cmd->arg_arr[0] == NULL)
		return (0);
	if (ft_strcmp("pwd", cmd->arg_arr[0]) == 0)
		return (1);
	if (ft_strcmp("cd", cmd->arg_arr[0]) == 0)
		return (1);
	if (ft_strcmp("echo", cmd->arg_arr[0]) == 0)
		return (1);
	if (ft_strcmp("export", cmd->arg_arr[0]) == 0)
		return (1);
	if (ft_strcmp("env", cmd->arg_arr[0]) == 0)
		return (1);
	if (ft_strcmp("unset", cmd->arg_arr[0]) == 0)
		return (1);
	if (ft_strcmp("exit", cmd->arg_arr[0]) == 0)
		return (1);
	return (0);
}
