#include "../minishell.h"

int piping(t_cmd *cmd)
{
    t_cmd   *tmp;
    int     **pipefd;
    int     index;
    int     res;
    int     len;

    index = 0;
    tmp = cmd;
    len = cmd_lenth(cmd);
    pipefd = malloc(sizeof(int *) * len + 1);
    if (!pipefd)
        return (5);
    pipefd[len] = '\0';
    while (tmp)
    {
        setup_pipe(tmp, pipefd, index);
        tmp = tmp->next;
    }
    free_file_discriptor(pipefd);
}