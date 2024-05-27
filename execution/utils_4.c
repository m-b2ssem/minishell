/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:46:38 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:46:38 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal;

void	herdoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	printf_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	free_file(t_cmd *cmd)
{
	if (cmd->file)
	{
		if (unlink(cmd->file) == -1)
		{
			ft_putstr_fd("there is an error deleting the file\n", 2);
		}
		free(cmd->file);
	}
}

void	free_new_dd(pid_t *pross_id, t_cmd *tmp)
{
	ft_putstr_fd("faild to fork", 2);
	close_fd(&tmp);
	free_cmd(tmp);
	free(pross_id);
	exit(1);
}

void	clean_exit_2(t_cmd *tmp, pid_t *pross_id, int status)
{
	close(2);
	close(1);
	close(0);
	close_fd(&tmp);
	free_env_list(tmp->env);
	free_cmd(tmp);
	free(pross_id);
	exit(status);
}
