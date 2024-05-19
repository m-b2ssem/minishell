#include "../minishell.h"


int	builtin_echo(t_cmd *cmd)
{
	int checker;
	int i;

	checker = 1;
	i = 1;
	if (cmd->arg_arr[i] && ft_strcmp(cmd->arg_arr[i], "-n") == 0)
	{
		checker = 0;
		i++;
	}
	while (cmd->arg_arr[i])
	{
		/*ft_putstr_fd("out 1:", 2);
		ft_putstr_fd(ft_itoa(cmd->fd_out), 2);
		write(2, "\n", 1);*/
		write(cmd->fd_out, cmd->arg_arr[i], ft_strlen(cmd->arg_arr[i]));
		//printf("%s", cmd->arg_arr[i]);
		i++;
	}
	if (checker)
		write(cmd->fd_out, "\n", 1);
	//printf("\n");
	return (0);
}
