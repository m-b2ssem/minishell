#include "../minishell.h"

int	builtin_echo(t_cmd *cmd)
{
	int	checker;
	int	i;

	checker = 1;
	i = 1;
	if (cmd->arg_arr[i] && ft_strcmp(cmd->arg_arr[i], "-n") == 0)
	{
		checker = 0;
		i++;
	}
	while (cmd->arg_arr[i])
	{
		write(cmd->fd_out, cmd->arg_arr[i], ft_strlen(cmd->arg_arr[i]));
		if (cmd->arg_arr[i + 1])
		{
			write(cmd->fd_out, " ", 1);
		}
		i++;
	}
	if (checker)
	{
		write(cmd->fd_out, "\n", 1);
	}
	return (0);
}
