#include "../minishell.h"

static void	update_new_ped(t_env **env, char *name, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	upate_oldpwd_pwd(t_env **env, char *oldpwd, int i)
{
	t_env	*tmp;

	tmp = *env;
	if (i == 1)
	{
		update_new_ped(env, "PWD", oldpwd);
	}
	if (i == 0)
	{
		while (tmp != NULL)
		{
			if (ft_strcmp("OLDPWD", tmp->name) == 0)
			{
				free(tmp->value);
				tmp->value = ft_strdup(oldpwd);
				return ;
			}
			tmp = tmp->next;
		}
	}
}

int	cd_to_home(t_cmd *cmd, char *home)
{
	if (cmd->arg_arr[1] == NULL)
	{
		if (chdir(home) != 0)
		{
			ft_putstr_fd("no dirctory with this name\n", 2);
			return (1);
		}
	}
	else if (cmd->arg_arr[1] != NULL && ft_strcmp("--", cmd->arg_arr[1]) == 0)
	{
		if (chdir(home) != 0)
		{
			ft_putstr_fd("no dirctory with this name\n", 2);
			return (1);
		}
	}
	else if (cmd->arg_arr[1] != NULL && ft_strcmp("-", cmd->arg_arr[1]) == 0)
	{
		if (chdir(home) != 0)
		{
			ft_putstr_fd("no dirctory with this name\n", 2);
			return (1);
		}
	}
	return (0);
}

int	cd_home(t_cmd *cmd)
{
	char	*home;
	char	*pwd;

	home = my_getenv("HOME", cmd->env);
	if (home == NULL)
	{
		ft_putstr_fd("couldn't find the home path\n", 2);
		return (1);
	}
	if (cd_to_home(cmd, home))
		return (1);
	pwd = getcwd(NULL, 0);
	upate_oldpwd_pwd(&cmd->env, pwd, 1);
	upate_oldpwd_pwd(&cmd->env, home, 0);
	return (0);
}

int	builtin_cd(t_cmd *cmd)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (cd_home(cmd))
		return (1);
	else if (cmd->arg_arr[1] != NULL && ft_strcmp("..", cmd->arg_arr[1]) == 0)
	{
		if (chdir("..") != 0)
		{
			ft_putstr_fd("no dirctory with this name\n", 2);
			return (1);
		}
	}
	else
	{
		if (cmd->arg_arr[1] != NULL && chdir(cmd->arg_arr[1]) != 0)
			return (ft_putstr_fd("no dirctory with this name\n", 2), 1);
	}
	pwd = getcwd(NULL, 0);
	upate_oldpwd_pwd(&cmd->env, pwd, 1);
	upate_oldpwd_pwd(&cmd->env, oldpwd, 0);
	return (0);
}
