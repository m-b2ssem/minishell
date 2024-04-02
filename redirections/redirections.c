#include "../minishell.h"

/*static int redirections_in(t_cmd *cmd, t_token token)
{
    if (token.type.REDIR_OUT)
    {
        cmd->fd_out = open(token.path, O_CREAT | O_RDWR | O_TRUNC, 0644)
        if (cmd.fd_out == -1)
            return (-1);
    }
    if (token.type.REDIR_DOUT)
    {
        cmd->fd_out = open(token.path, O_CREAT | O_RDWR | O_APPEND, 0644)
        if (cmd.fd_out == -1)
            return (-1);
    }
    return (0)
}*/

static int redirections_out(t_cmd *cmd, t_token *token)
{
    if (token->type.REDIR_OUT)
    {
        cmd->fd_out = open(token->path, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (cmd->fd_out == -1)
            return (-1);
    }
    if (token->type.REDIR_DOUT)
    {
        cmd->fd_out = open(token->path, O_CREAT | O_RDWR | O_APPEND, 0644);
        if (cmd->fd_out == -1)
            return (-1);
    }
    return (0);
}


int redirections(t_cmd *cmd)
{
    t_token *tmp;

    tmp = cmd->token;
    while (tmp)
    {
        /*if (tmp->type.REDIR_DIN || tmp->type.REDIR_DOUT)
        {
            if (redirections_in(cmd, tmp))
                return (-1);
        }*/
        if (tmp->type.REDIR_DOUT || tmp->type.REDIR_OUT)
        {
            if (redirections_out(cmd, tmp))
                return (-1);
        }
        tmp = tmp->next;
    }
    return (0);
}
