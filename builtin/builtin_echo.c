#include "../minishell.h"

int builtin_echo(t_cmd *cmd)
{
    int checker;
    int i;

    checker = 0;
    i = 0;
    if (cmd->arg_arr[i] && ft_strcmp(cmd->arg_arr[i], "-n") == 0)
    {
        checker = 1;
        i++;
    }
    while (cmd->arg_arr[i])
    {
        printf("%s", cmd->arg_arr[i]);
        i++;
    }
    if (checker)
        printf("\n");
    return (0);
}