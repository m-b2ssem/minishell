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
        builtin_export(cmd);
    if (ft_strcmp("env", cmd->builtin) == 0)
        builtin_env(env);
    if (ft_strcmp("unset", cmd->builtin) == 0)
        builtin_unset(cmd, cmd->args);
    /**
    if (ft_strcmp("exit", cmd) == 0)
        builtin_exit(cmd); todo
    */
}

void    execute(t_cmd *cmd, char **env)
{
    t_value cur = cmd->token->type;
    if (cur.REDIR_DIN != 0 || cur.REDIR_DOUT != 0 || cur.REDIR_IN != 0 || cur.REDIR_OUT != 0)
        redirections(cmd);
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
    cmd->token = (t_token *)malloc(sizeof(t_token) * 1);
    if (!cmd->token)
    {
        return 0;
    }
    cmd->token->type = (t_value *)malloc(sizoeof(t_value) * 1);
    cmd->token->type.REDIR_OUT = atoi(argv[2]);
    cmd->token->path = argv[3];
    cmd->env = env;
    
    execute(cmd, env);
    free(cmd);
    return 0;
}