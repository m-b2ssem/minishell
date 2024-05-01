#include "../minishell.h"

extern int exit_status;



int    custom_exe(t_cmd *cmd, t_cmd *tmp, pid_t *pross_id)
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
        builtin_env(*(cmd->env));
    if (ft_strcmp("unset", cmd->token->builtin) == 0)
        builtin_unset(cmd->env, cmd);
    if (ft_strcmp("exit", cmd->token->builtin) == 0)
        builtin_exit(cmd, tmp, pross_id);
    if (cur.REDIR_DIN != 0 || cur.REDIR_DOUT != 0 || cur.REDIR_IN != 0 || cur.REDIR_OUT != 0)
        redirections(cmd);
    return (0);
}

char **env_to_char(t_env *env)
{
    t_env *tmp;
    char **new_env;
    int i;

    i = 0;
    tmp = env;
    while (tmp != NULL)
    {
        i++;
        tmp = tmp->next;
    }
    new_env = malloc(sizeof(char *) * (i + 1));
    if (!new_env)
        return (NULL);
    i = 0;
    tmp = env;
    while (tmp != NULL)
    {
        if (tmp->export == 1)
        {
            new_env[i] = ft_strjoin(tmp->name, "=");
            new_env[i] = ft_strjoin(new_env[i], tmp->value);
        }
        else
            new_env[i] = ft_strjoin(tmp->name, "=");
        i++;
        tmp = tmp->next;
    }
    new_env[i] = NULL;
    return (new_env);
}

void custom_exe_on_child(t_cmd *cmd, pid_t *pross_id, t_cmd *tmp)
{
    struct stat fileStat;
    char **new_env;

    if (cmd->token->builtin != NULL)
    {
        custom_exe(cmd, tmp, pross_id);
        free_list(cmd->env);
        clean_exit(tmp, pross_id, 110);
    }
    else
    {
        cmd->path = get_bin_path(cmd->arg_arr[0]);
        printf("path: %s\n", cmd->path);
        //if (cmd->path == NULL)
            //clean_exit(tmp, pross_id, 127);
        new_env = env_to_char(*(cmd->env));
        if (new_env == NULL)
            clean_exit(tmp, pross_id, 127);
        execve(cmd->path, cmd->arg_arr, new_env);
        if(stat(cmd->arg_arr[0], &fileStat) == 0)
        {
            write(2, "minishell: ", 11);
            write(2, cmd->arg_arr[0], ft_strlen(cmd->arg_arr[0]));
            write(2, ": Permission denied\n", 21);
            free(new_env);
            clean_exit(tmp, pross_id, 126);
        }
        free(new_env);
        clean_exit(tmp, pross_id, 127);
    }
}

void eof_handler(int sig_num)
{
    (void)sig_num;
    write(1, "signal\n", 7);
    exit(0);
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


int    execute(t_cmd *cmd, t_env **env)
{
    pid_t   *pross_ids;
    t_cmd    *tmp;
    int     len;
    int     res;
    int     i;
    (void)env;

    i = 0;
    tmp = cmd;
    len = cmd_lenth(cmd);
    pross_ids = ft_calloc(len, sizeof(pid_t));
    if (!pross_ids)
        return (2);
    res = piping(cmd);
    if (res)
        return (3); // check which value you should return.
    signal(EOF, eof_handler);
    if (cmd->token->builtin != NULL && cmd_lenth(cmd) == 1)
    {
        custom_exe(cmd, tmp, pross_ids);
        close_fd(tmp);
        return (50);
    }
    else
    {
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