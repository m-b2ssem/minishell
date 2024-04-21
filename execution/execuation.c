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

int close_fd(t_cmd *cmd)
{
    t_cmd   *cur;

    cur = cmd;
    while (cur)
    {
        if (cur->fd_in != 0)
            close(cur->fd_in);
        if (cur->fd_out != 1)
            close(cur->fd_out);
        cur = cur->next;
    }
    return (0);
}
void custom_exe_on_child(t_cmd *cmd, pid_t *pross_id)
{
    (void)pross_id;
    if (cmd->token->builtin != NULL)
    {
        custom_exe(cmd, cmd->env);
        exit(0);
    }
    else
    {
        /*printf("path: %s\n", cmd->path);
        printf("arg_arr: %s\n", cmd->arg_arr[1]);
        printf("fd_in: %d\n", cmd->fd_in);
        printf("fd_out: %d\n", cmd->fd_out);*/
        execve(cmd->path, cmd->arg_arr, cmd->env);
        exit(0);
    }
}

int child_procces(t_cmd *cmd,  pid_t *pross_id, int i)
{
    pross_id[i] = fork();
    if (pross_id[i] == -1)
        exit(1);
    if (pross_id[i] == 0)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        dup2(cmd->fd_out, STDOUT_FILENO);
        close_fd(cmd);
        custom_exe_on_child(cmd, pross_id);
    }
    return (0);
}

void wait_pid(pid_t *pross_id, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        waitpid(pross_id[i], NULL, 0);
        i++;
    }
}

int    execute(t_cmd *cmd, char **env)
{
    pid_t   *pross_ids;
    int     len;
    int     res;
    int     i;

    i = 0;
    len = cmd_lenth(cmd);
    pross_ids = ft_calloc(len, sizeof(pid_t));
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
    {
        while (cmd != NULL)
        {
            child_procces(cmd, pross_ids, i);
            if (cmd->fd_in != 0)
		        close(cmd->fd_in);
	        if (cmd->fd_out != 1)
		        close(cmd->fd_out);
            cmd = cmd->next;
        }
        
    }
    wait_pid(pross_ids, len);
    free(pross_ids);
    return (0);
}