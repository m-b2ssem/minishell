#include "../minishell.h"

//https://github.com/cclaude42/minishell.git

int builtin_cd(t_cmd *cmd)
{
    //char *odl_pwd = getcwd(NULL, 0);
    if (cmd->arg_arr[1] == NULL)
    {
        //here I should pass the home dirctory 
        if (chdir("/Users/bassem") != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else if (ft_strcmp("--", cmd->arg_arr[1]) == 0)
    {
        if (chdir(HOME) != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
    else if (ft_strcmp("-",  cmd->arg_arr[1]) == 0)
    {
        if (chdir("/Users/bassem") != 0)
        {
            ft_putstr_fd("no dirctory with this name\n", 2);
            return (1);
        }
    }
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
    // for testing
    char *new_pwd = getcwd(NULL, 0);
    // we need to update the old pwd and the new pwd in the env arry
    printf("%s", new_pwd);
    return (0);
}