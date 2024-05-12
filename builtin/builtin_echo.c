#include "../minishell.h"

int builtin_echo(t_cmd *cmd)
{
    int checker;
    //char *str = NULL;
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
        //str = check_for_env_value(cmd->arg_arr[i], cmd->env);
        //if (str == NULL)
            //return (10);
        printf("%s", cmd->arg_arr[i]);
        i++;
    }
    if (checker)
        printf("\n");
    return (0);
}