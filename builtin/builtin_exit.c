#include "../minishell.h"

extern int exit_status;

static int ft_isnumbers(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] < '0' || str[i] > '9')
            return (0);
        i++;
    }
    return (1);
}

void builtin_exit(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id)
{
    printf("exit\n");
    if (cmd->arg_arr[1] != NULL)
    {
        if (cmd->arg_arr[1] && cmd->arg_arr[2] != NULL)
        {
            printf("minishell: exit: too many arguments\n");
            exit_status = 1;
            return ;
        }
        if (!ft_isnumbers(cmd->arg_arr[1]))
        {
            printf("minishell: exit: %s: numeric argument required\n", cmd->arg_arr[1]);
            clean_exit(tmp, pross_id, 2);
        }
        exit_status = ft_atoi(cmd->arg_arr[1]);
        clean_exit(tmp, pross_id, exit_status);
    }
    clean_exit(tmp, pross_id, 0);
}