#include "../minishell.h"


int	builtin_env(t_env *env, t_cmd *cmd)
{
	if (!env)
		return (1);
	if (cmd->arg_arr[1] != NULL)
	{
		write(2, "env: '", 7);
		write(2, cmd->arg_arr[1], ft_strlen(cmd->arg_arr[1]));
		write(2, "': No such file or directory\n", 30);
		return (1);
	}
	while (env)
	{
		if (env->export == 1)
		{
			printf("%s=%s\n", env->name, env->value);
		}
		env = env->next;
	}
	return (0);
}
