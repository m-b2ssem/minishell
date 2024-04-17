#include "../minishell.h"

int    custom_exe(t_cmd *cmd, char **env)
{
    t_rid cur = cmd->token->type;
    if (ft_strcmp("pwd", cmd->token->builtin) == 0)
        builtin_pwd();
    if (ft_strcmp("cd", cmd->token->builtin) == 0)
        builtin_cd(cmd);
    if (ft_strcmp("echo", cmd->token->builtin) == 0)
        builtin_echo(cmd);
    if (ft_strcmp("export", cmd->token->builtin) == 0)
        builtin_export(cmd);
    if (ft_strcmp("env", cmd->token->builtin) == 0)
        builtin_env(env);
    if (ft_strcmp("unset", cmd->token->builtin) == 0)
        builtin_unset(cmd, cmd->args);
    /**
    if (ft_strcmp("exit", cmd) == 0)
        builtin_exit(cmd); todo
    */
    if (cur.REDIR_DIN != 0 || cur.REDIR_DOUT != 0 || cur.REDIR_IN != 0 || cur.REDIR_OUT != 0)
        redirections(cmd);
    return (0);
}
int cmd_lenth(t_cmd *cmd)
{
    t_cmd   *cur;
    int     i;

    cur = cmd;
    i = 0;
    while (cur)
    {
        i++;
        cur = cur->next;
    }
    return (i);
}

/*int one_fork(t_cmd *cmd, pid_t *pross_ids, char **env)
{
    dup2(cmd->fd_in, STDIN_FILENO);
	dup2(cmd->fd_out, STDOUT_FILENO);
    pross_ids[0] = fork();
    if (pross_ids[0] == -1)
        exit(1);
    if (pross_ids[0] == 0)
    {
        execve(cmd->path, cmd->arg_arr, env);
    }
    free(pross_ids);
    return (0);
}*/

int child_procces(t_cmd *cmd, pid_t *pross_ids, char **env)
{
    
}

int    execute(t_cmd *cmd, char **env)
{
    pid_t   *pross_ids;
    int     res;

    pross_ids = malloc(cmd_lenth(cmd) * sizeof(pid_t));
    if (!pross_ids)
        return (2);
    res = piping(cmd);
    if (res)
        return (3); // check which value you should return.
    if (cmd->token->builtin != NULL && cmd_lenth(cmd) == 1)
    {
        custom_exe(cmd, env);
        return (0);
    }
    else
        child_procces(cmd, pross_ids, env);

    return (0);
}