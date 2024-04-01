#include "../minishell.h"

//https://github.com/cclaude42/minishell.git

int builtin_cd(t_cmd *cmd)
{
    char *odl_pwd = getcwd(NULL, 0);
    if (cmd->builtin == NULL)
    {
        printf("no builtin was passed\n");
        return (1);
    }
    if (cmd->path == NULL)
    {
        //here I should pass the home dirctory 
        if (chdir("/Users/bassem") != 0)
        {
            printf("no dirctory with this name\n");
            return (1);
        }
    }
    else if (ft_strcmp("--", cmd->path) == 0)
    {
        if (chdir(HOME) != 0)
        {
            printf("no dirctory with this name\n");
            return (1);
        }
    }
    else if (ft_strcmp("-", cmd->path) == 0)
    {
        if (chdir("/Users/bassem") != 0)
        {
            printf("no dirctory with this name\n");
            return (1);
        }
    }
    else if (ft_strcmp("..", cmd->path) == 0)
    {
        if (chdir("..") != 0)
        {
            printf("no dirctory with this name\n");
            return (1);
        }
    }
    else
    {
        if(chdir(cmd->path) != 0)
        {
            printf("no dirctory with this name\n");
            return (1);
        }
    }
    // for testing
    char *new_pwd = getcwd(NULL, 0);
    // we need to update the old pwd and the new pwd in the env arry
    printf("%s", new_pwd);
    return (0);
}