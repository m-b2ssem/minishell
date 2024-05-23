#include "../minishell.h"

extern sig_atomic_t	g_signal;

void	handle_non_builtin(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp)
{
	struct stat	file_stat;
	char		**new_env;

	cmd->path = get_path(cmd->arg_arr[0], cmd->env);
	if (cmd->path == NULL)
	{
		clean_exit(tmp, pross_id, 127);
	}
	new_env = env_to_char(cmd->env);
	if (new_env == NULL)
		clean_exit(tmp, pross_id, 127);
	execve(cmd->path, cmd->arg_arr, new_env);
	if (stat(cmd->arg_arr[0], &file_stat) == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->arg_arr[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(new_env);
		clean_exit(tmp, pross_id, 126);
	}
	free(new_env);
	clean_exit(tmp, pross_id, 127);
}

void	custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp)
{
	int	status;

	status = 0;
	if (builtin(cmd))
	{
		status = custom_exe(cmd, tmp, pross_id);
		clean_exit(tmp, pross_id, status);
	}
	else
	{
		handle_non_builtin(cmd, pross_id, tmp);
	}
}

void	loop_inside_execute(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp)
{
	int	i;

	i = 0;
	while (cmd != NULL)
	{
		pross_id[i] = fork();
		if (pross_id[i] == -1)
		{
			ft_putstr_fd("faild to fork", 2);
			free_cmd(tmp);
			free(pross_id);
			exit(1);
		}
		if (pross_id[i] == 0)
		{
			child_signal();
			if (redirections(cmd))
			{
				clean_exit(tmp, pross_id, 126);
			}
			dup2(cmd->fd_in, STDIN_FILENO);
			dup2(cmd->fd_out, STDOUT_FILENO);
			close_fd(tmp);
			custom_exe_on_child(cmd, pross_id, tmp);
		}
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		cmd = cmd->next;
		i++;
	}
}

int	execute(t_cmd **cmd1)
{
	pid_t	*pross_ids;
	t_cmd	*tmp;
	int		res;
	int		status;
	t_cmd	*cmd;

	status = 0;
	cmd = *cmd1;
	tmp = cmd;
	if (cmd_lenth(tmp) == 0)
		return (0);
	pross_ids = ft_calloc(cmd_lenth(cmd), sizeof(pid_t));
	if (!pross_ids)
		return (10);
	res = piping(cmd);
	if (res)
		return (free(pross_ids), 11); // check which value you should return.
	if (builtin(cmd) && cmd_lenth(cmd) == 1)
		return (one_operation(cmd, tmp, pross_ids) + g_signal);
	else
		loop_inside_execute(cmd, pross_ids, tmp);
	parent_signals(); // check
	status = wait_pid(pross_ids, cmd_lenth(cmd));
	parent_signals(); // check
	free(pross_ids);
	return (status);
}
