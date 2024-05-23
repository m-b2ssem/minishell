#include "../minishell.h"

static int	ft_isnumbers(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		if (ft_isalpha(str[i]) || str[i] == '+' || str[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id)
{
	int	exit_status;

	exit_status = 0;
	if (cmd->arg_arr[1] && cmd->arg_arr[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	printf("exit\n");
	if (cmd->arg_arr[1] != NULL)
	{
		if (!ft_isnumbers(cmd->arg_arr[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, cmd->arg_arr[1], ft_strlen(cmd->arg_arr[1]));
			write(2, ": numeric argument required\n", 29);
			clean_exit(tmp, pross_id, 2);
		}
		exit_status = ft_atoi(cmd->arg_arr[1]);
		clean_exit(tmp, pross_id, exit_status);
	}
	clean_exit(tmp, pross_id, 0);
	return (0);
}
