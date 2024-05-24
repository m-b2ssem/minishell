#include "../minishell.h"

int	builtin_export_checker(char *arr)
{
	int	i;
	int	size;

	if (ft_strchr(arr, '=') != NULL)
		size = find_char(arr);
	else
		size = ft_strlen(arr);
	if (size == 0)
		return (1);
	if (arr[0] == '-')
		return (2);
	if (!is_valid_char(arr[0]))
		return (1);
	i = 1;
	while (i < size)
	{
		if (!is_valid_char_rest(arr[i]))
			return (1);
		i++;
	}
	return (0);
}

int	export_checker(t_cmd *cmd)
{
	int	res;

	res = 0;
	if (cmd->arg_arr[1] != NULL)
	{
		res = builtin_export_checker(cmd->arg_arr[1]);
		if (res != 0)
		{
			if (res == 1)
			{
				write(2, "minishell: export: '", 21);
				write(2, cmd->arg_arr[1], ft_strlen(cmd->arg_arr[1]));
				write(2, "': not a valid identifier\n", 27);
			}
			else
			{
				write(2, "minishell: export: ", 20);
				write(2, &cmd->arg_arr[1][0], 1);
				write(2, &cmd->arg_arr[1][1], 1);
				write(2, ": invalid option\n", 18);
			}
			return (1);
		}
	}
	return (0);
}
