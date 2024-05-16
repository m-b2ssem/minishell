#include "../minishell.h"

static int redirections_in(t_cmd *cmd, t_token *token)
{
    if (token->type == REDIR_IN)
    {
        if (cmd->fd_in != 0)
            close(cmd->fd_in);
        cmd->fd_in = open(token->string, O_RDONLY);
        if (cmd->fd_in == -1)
            return (-1);
    }
    if (token->type == DELIM)
    {
        if (cmd->fd_in != 0)
            close(cmd->fd_in);
        cmd->fd_in = heredoc(cmd, token->next->string);
        if (cmd->fd_in == -1)
            return (-1);
    }
    return (0);
}


static int redirections_out(t_cmd *cmd, t_token *token)
{
    if (token->type == REDIR_OUT)
    {
        if (cmd->fd_out != 1)
            close(cmd->fd_out);
        cmd->fd_out = open(token->next->string, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (cmd->fd_out == -1)
            return (-1);
    }
    if (token->type == APPEND)
    {
        if (cmd->fd_out != 1)
            close(cmd->fd_out);
        cmd->fd_out = open(token->string, O_CREAT | O_RDWR | O_APPEND, 0644);
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
        if (tmp->type == REDIR_IN || tmp->type == DELIM)
        {
            if (redirections_in(cmd, tmp))
                return (-1);
        }
        if (tmp->type == REDIR_OUT || tmp->type == APPEND)
        {
            if (redirections_out(cmd, tmp))
                return (-1);
        }
        tmp = tmp->next;
    }
    return (0);
}
