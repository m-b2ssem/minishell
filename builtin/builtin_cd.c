#include "../minishell.h"

int cd_home(t_cmd *cmd)
{
    char *home;

    home = my_getenv("HOME", cmd->env);
    if (home == NULL)
    {
        ft_putstr_fd("no dirctory with this name\n", 2);
        return (1);
    }
    if (cmd->arg_arr[1] == NULL)
    {
        if (chdir(home) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else if (ft_strcmp("--", cmd->arg_arr[1]) == 0)
    {
        if (chdir(home) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else if (ft_strcmp("-",  cmd->arg_arr[1]) == 0)
    {
        if (chdir(home) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    free(home);
    return (0);
}

int builtin_cd(t_cmd *cmd)
{
    if (cd_home(cmd))
        return (1);
    else if (ft_strcmp("..",  cmd->arg_arr[1]) == 0)
    {
        if (chdir("..") != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else
    {
        if(chdir(cmd->arg_arr[1]) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    return (0);
}