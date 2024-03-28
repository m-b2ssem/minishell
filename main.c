#include "minishell.h"

void    custom_exe(t_cmd *cmd, char **env)
{
    if (ft_strcmp("pwd", cmd->builtin) == 0)
        builtin_pwd();
    if (ft_strcmp("cd", cmd->builtin) == 0)
        builtin_cd(cmd);
    if (ft_strcmp("echo", cmd->builtin) == 0)
        builtin_echo(cmd);
    if (ft_strcmp("export", cmd->builtin) == 0)
        builtin_export(cmd, env);
    if (ft_strcmp("env", cmd->builtin) == 0)
        builtin_env(env);
    if (ft_strcmp("unset", cmd->builtin) == 0)
        builtin_unset(cmd, cmd->args);
    /*
    if (ft_strcmp("exit", cmd) == 0)
        builtin_exit(cmd); todo
    */
}

void    execute(t_cmd *cmd, char **env)
{
    custom_exe(cmd, env);
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
    cmd->args = argv[2];
    cmd->env = env;
    
    execute(cmd, env);
    free(cmd);
    return 0;
}