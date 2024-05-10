#include "minishell.h"


int main(int argc,char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    int status;
    char *str;
    t_cmd *cmd;
    t_env **envp;

    status = 0;
    initialize_env_variables(envp, env);
    while (1)
    {
        str = readline("minishell> ");
        if (str == NULL)
        {
            free_everything_exit(cmd);
        }
        add_history(str);
        cmd = parse_cmd(str);
        status = execute(cmd, cmd->env);
        free_everything(cmd);
    }
    return (0);
}