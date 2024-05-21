#include "../minishell.h"

static void upate_oldpwd_pwd(t_env **env, char *oldpwd, int i)
{
    t_env *tmp;

    tmp = *env;
    if (i == 1)
    {
        while (tmp != NULL)
        {
            if (ft_strcmp("PWD", tmp->name) == 0)
            {
                free(tmp->value);
                tmp->value = ft_strdup(oldpwd);
                return ;
            }
            tmp = tmp->next;
        }
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

int cd_home(t_cmd *cmd)
{
    char *home;
    char *pwd;

    home = my_getenv("HOME", cmd->env);
    if (home == NULL)
    {
        ft_putstr_fd("couldn't find the home path\n", 2);
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
    else if (cmd->arg_arr[1] != NULL &&  ft_strcmp("--", cmd->arg_arr[1]) == 0)
    {
        if (chdir(home) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else if (cmd->arg_arr[1] != NULL &&  ft_strcmp("-",  cmd->arg_arr[1]) == 0)
    {
        if (chdir(home) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    pwd = getcwd(NULL, 0);
    upate_oldpwd_pwd(&cmd->env, pwd, 1);
    upate_oldpwd_pwd(&cmd->env, home, 0);
    return (0);
}

int builtin_cd(t_cmd *cmd)
{
    char *oldpwd;
    char *pwd;

    oldpwd = getcwd(NULL, 0);
    if (cd_home(cmd))
        return (1);
    else if (cmd->arg_arr[1] != NULL && ft_strcmp("..",  cmd->arg_arr[1]) == 0)
    {
        if (chdir("..") != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else
    {
        if(cmd->arg_arr[1] != NULL &&  chdir(cmd->arg_arr[1]) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    pwd = getcwd(NULL, 0);
    upate_oldpwd_pwd(&cmd->env, pwd, 1);
    upate_oldpwd_pwd(&cmd->env, oldpwd, 0);
    return (0);
}