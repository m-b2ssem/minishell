#include "../minishell.h"

extern sig_atomic_t	g_signal;

int	custom_exe(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id)
{
	int	status;

<<<<<<< HEAD
	status = 0;
	printf("arg: %s\n", cmd->arg_arr[0]);
	if (ft_strcmp("pwd", cmd->arg_arr[0]) == 0)
		status = builtin_pwd();
	if (ft_strcmp("cd", cmd->arg_arr[0]) == 0)
		status = builtin_cd(cmd);
	if (ft_strcmp("echo", cmd->arg_arr[0]) == 0)
		status = builtin_echo(cmd);
	if (ft_strcmp("export", cmd->arg_arr[0]) == 0)
		status = builtin_export(cmd);
	if (ft_strcmp("env", cmd->arg_arr[0]) == 0)
		status = builtin_env(cmd->env);
	if (ft_strcmp("unset", cmd->arg_arr[0]) == 0)
		status = builtin_unset(&cmd->env, cmd);
	if (ft_strcmp("exit", cmd->arg_arr[0]) == 0)
		status = builtin_exit(cmd, tmp, pross_id);
	return (status);
=======
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
        status = builtin_env(cmd->env);
    if (ft_strcmp("unset", cmd->arg_arr[0]) == 0)
        status = builtin_unset(&cmd->env, cmd);
    if (ft_strcmp("exit", cmd->arg_arr[0]) == 0)
        status = builtin_exit(cmd, tmp, pross_id);
    return (status);
>>>>>>> 70ce852 (fix the heredoc)
}

char	**env_to_char(t_env *env)
{
	t_env	*tmp;
	char	**new_env;
	int		i;

	i = 0;
	tmp = env;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	tmp = env;
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

void	custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp)
{
	struct stat	fileStat;
	char		**new_env;
	int			status;

	status = 0;
	if (builtin(cmd))
	{
		(void)status;
		status = custom_exe(cmd, tmp, pross_id);
		clean_exit(tmp, pross_id, status);
	}
	else
	{
		cmd->path = get_path(cmd->arg_arr[0]);
		printf("path: %s\n", cmd->path);
		if (cmd->path == NULL)
		{
			clean_exit(tmp, pross_id, 127);
		}
		new_env = env_to_char(cmd->env);
		if (new_env == NULL)
			clean_exit(tmp, pross_id, 127);
		execve(cmd->path, cmd->arg_arr, new_env);
		if (stat(cmd->arg_arr[0], &fileStat) == 0)
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
}

int	child_process(t_cmd *cmd, pid_t *pross_id, int i, t_cmd *tmp)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
		dup2(cmd->fd_in, STDIN_FILENO);
		dup2(cmd->fd_out, STDOUT_FILENO);
		close_fd(tmp);
		custom_exe_on_child(cmd, pross_id, tmp);
	}
	return (0);
}

int	execute(t_cmd **cmd1, t_env *env)
{
	pid_t	*pross_ids;
	t_cmd	*tmp;
	int		len;
	int		res;
	int		i;
	int		status;
	t_cmd	*cmd;

<<<<<<< HEAD
	(void)env;
	i = 0;
	status = 0;
	cmd = *cmd1;
	tmp = cmd;
	len = 0;
	// printf("here\n");
	len = cmd_lenth(cmd);
	// printf("len: %d\n", len);
	pross_ids = ft_calloc(len, sizeof(pid_t));
	if (!pross_ids)
		return (10);
	res = piping(cmd);
	if (res)
		return (free(pross_ids), 11); // check which value you should return.
	if (builtin(cmd) && cmd_lenth(cmd) == 1)
	{
		redirections(cmd);
		status = custom_exe(cmd, tmp, pross_ids);
		close_fd(tmp);
		free(pross_ids);
		return ((status + g_signal));
	}
	else
	{
		while (cmd != NULL)
		{
			redirections(cmd);
			child_process(cmd, pross_ids, i, tmp);
			if (cmd->fd_in != 0)
				close(cmd->fd_in);
			if (cmd->fd_out != 1)
				close(cmd->fd_out);
			cmd = cmd->next;
		}
	}
	parent_signals(); // check
	status = wait_pid(pross_ids, len);
	parent_signals(); // check
	free(pross_ids);
	return (status);
=======
    i = 0;
    status = 0;
    cmd = *cmd1;
    tmp = cmd;
    len = 0;


    len = cmd_lenth(cmd);
    pross_ids = ft_calloc(len, sizeof(pid_t));
    if (!pross_ids)
        return (10);
    res = piping(cmd);
    if (res)
        return (free(pross_ids),11); // check which value you should return.
    if (builtin(cmd) && cmd_lenth(cmd) == 1)
    {
        redirections(cmd);
        status = custom_exe(cmd, tmp, pross_ids);
        close_fd(tmp);
        free(pross_ids);
        return ((status + g_signal));
    }
    else
    {
        while (cmd != NULL)
        {
            redirections(cmd);
            child_process(cmd, pross_ids, i, tmp);
            if (cmd->fd_in != 0)
		        close(cmd->fd_in);
	        if (cmd->fd_out != 1)
		        close(cmd->fd_out);
            cmd = cmd->next;
        }
    }
    parent_signals(); // check
    status = wait_pid(pross_ids, len);
    parent_signals(); // check
    free(pross_ids);
    return (status);
>>>>>>> 70ce852 (fix the heredoc)
}
