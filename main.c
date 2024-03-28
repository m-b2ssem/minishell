#include "minishell.h"

void    custom_exe(t_cmd *cmd)
{
    if (ft_strcmp("pwd", cmd->builtin) == 0)
        builtin_pwd();
    if (ft_strcmp("cd", cmd->builtin) == 0)
        builtin_cd(cmd);
    if (ft_strcmp("echo", cmd) == 0)
        builtin_echo(cmd); //todo
    /*
    if (ft_strcmp("export", cmd) == 0)
        builtin_export(cmd); todo
    if (ft_strcmp("unset", cmd) == 0)
        builtin_unset(cmd); todo
    if (ft_strcmp("env", cmd) == 0)
        builtin_env(cmd); todo
    if (ft_strcmp("exit", cmd) == 0)
        builtin_exit(cmd); todo
    */
}

void    execute(t_cmd *cmd, char **env)
{
    (void)env;
    custom_exe(cmd);
}
int main(int argc,char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    t_cmd   *cmd;
    cmd = (t_cmd *)malloc(sizeof(t_cmd) * 1);
    if (!cmd)
        return 0;
    cmd->builtin = argv[1];
    cmd->path = argv[2];
    execute(cmd, env);
    free(cmd);
    return 0;
}