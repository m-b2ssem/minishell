#include "../minishell.h"

static void free_paths(char **paths)
{
    int i = 0;
    while (paths[i] != NULL)
    {
        free(paths[i]);
        i++;
    }
    free(paths);
}


char *get_bin_path(char *command)
{
    char *path;
    char **paths;
    char *bin_path;
    char *tmp;
    int i;
    
    i = 0;
    path = getenv("PATH");
    if (path == NULL)
        return (NULL);
    paths = ft_split(path, ':');
    if (paths == NULL)
        return (NULL);
    while (paths[i] != NULL)
    {
        bin_path = ft_strjoin(paths[i], "/");
        if (bin_path == NULL)
            return (free_paths(paths),NULL);
        tmp = ft_strjoin(bin_path, command);
        if (tmp == NULL)
            return (free_paths(paths), free(bin_path),NULL);
        if (access(tmp, F_OK) == 0)
        {
            free(bin_path);
            free_paths(paths);
            return (tmp);
        }
        free(bin_path);
        free(tmp);
        i++;
    }
    free_paths(paths);
    return (NULL);
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

void clean_exit(t_cmd *tmp, pid_t *pross_id, int status)
{
    free_cmd(tmp);
    free(pross_id);
    exit(status);
}

void free_cmd(t_cmd *cmd)
{
    t_cmd *tmp;
    while (cmd != NULL)
    {
        free(cmd->arg_arr);
        free(cmd->token);
        tmp = cmd;
        cmd = cmd->next;
        free(tmp);
    }
}

void wait_pid(pid_t *pross_id, int len)
{
    int i;
    int status;

    i = 0;
    while (i < len)
    {
        waitpid(pross_id[i], &status, 0);
        printf("status: %d\n", WEXITSTATUS(status));
        i++;
    }
}

