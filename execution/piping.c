#include "../minishell.h"

static	int	free_pipe(int **pipefd)
{
	int	i;

	i = 0;
	while (pipefd[i])
	{
		free(pipefd[i]);
		i++;
	}
	free(pipefd);
	return (0);
}

static	int	setup_pipe(t_cmd *cmd, int **pipefd, int index)
{
	if (pipe(pipefd[index]) == -1)
	{
		printf("pipe error\n");
		return (6);
	}
	if (index == 0)
		cmd->fd_in = STDIN_FILENO;
	else
		cmd->fd_in = pipefd[index - 1][0];
	if (cmd->next == NULL)
	{
		close(pipefd[index][0]);
		close(pipefd[index][1]);
		cmd->fd_out = STDOUT_FILENO;
	}
	else
		cmd->fd_out = pipefd[index][1];
	return (0);
}

int	piping(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		**pipefd;
	int		index;
	int		len;

	index = 0;
	tmp = *cmd;
	len = cmd_lenth(tmp);
	pipefd = malloc(sizeof(int *) * (len + 1));
	if (!pipefd)
		return (5);
	pipefd[len] = NULL;
	while (tmp)
	{
		pipefd[index] = malloc(sizeof(int) * 2);
		if (!pipefd[index])
			return (free_pipe(pipefd), 5);
		if (setup_pipe(tmp, pipefd, index))
			return (free_pipe(pipefd), 6);
		tmp = tmp->next;
		index++;
	}
	if (redirections(cmd, pipefd))
		return (2);
	return (0);
}
