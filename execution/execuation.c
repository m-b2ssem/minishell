#include "../minishell.h"

extern int exit_status;



int    custom_exe(t_cmd *cmd, char **env, t_cmd *tmp, pid_t *pross_id)
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
    if (ft_strcmp("exit", cmd->token->builtin) == 0)
        builtin_exit(cmd, tmp, pross_id);
    if (cur.REDIR_DIN != 0 || cur.REDIR_DOUT != 0 || cur.REDIR_IN != 0 || cur.REDIR_OUT != 0)
        redirections(cmd);
    return (0);
}

void custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp)
{
    struct stat fileStat;
    if (cmd->token->builtin != NULL)
    {
        custom_exe(cmd, cmd->env, tmp, pross_id);
        free_cmd(tmp); // free cmd
        free(pross_id);
        exit(0);
    }
    else
    {
        cmd->path = get_bin_path(cmd->arg_arr[0]);
        //if (cmd->path == NULL)
            //clean_exit(tmp, pross_id, 127);
        execve("hghfgh", cmd->arg_arr, cmd->env);
        printf("dfshbgfhnsrghnfsf\n");
        if(stat(cmd->arg_arr[0], &fileStat) == 0)
            return (printf("Permissions deneid\n"),free_cmd(tmp), free(pross_id), exit(126));
        free_cmd(tmp); // free cmd
        free(pross_id);
        exit(127);
    }
}

int child_procces(t_cmd *cmd,  pid_t *pross_id, int i, t_cmd *tmp)
{
    pross_id[i] = fork();
    if (pross_id[i] == -1)
    {
        printf("fork failed\n");
        free_cmd(tmp);
        free(pross_id);
        exit(1);
    }
    if (pross_id[i] == 0)
    {
        dup2(cmd->fd_in, STDIN_FILENO);
        dup2(cmd->fd_out, STDOUT_FILENO);
        close_fd(tmp);
        custom_exe_on_child(cmd, pross_id, tmp);
    }
    return (0);
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
        custom_exe(cmd, env, cmd, pross_ids);
        return (0);
    }
    else
    {
        t_cmd *tmp = cmd;
        while (cmd != NULL)
        {
            child_procces(cmd, pross_ids, i, tmp);
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