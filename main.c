#include "minishell.h"


int main(int argc,char *argv[], char *env[])
{
    (void)argc;
    t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return 1;

    cmd->token = (t_token *)malloc(sizeof(t_token));
    if (!cmd->token) {
        free(cmd);
        return 1;
    }

    // Initialize all fields
    cmd->token->type.REDIR_DIN = 0;
    cmd->token->type.REDIR_IN = 0;
    cmd->token->type.REDIR_OUT = 0;
    cmd->token->type.REDIR_DOUT = 0;
    cmd->token->path = argv[1];
    cmd->token->next = NULL;
    cmd->env = env;
    cmd->args = NULL;
    cmd->arg_arr = malloc(sizeof(char *) * 3);
    if (!cmd->arg_arr)
        return 5;
    cmd->arg_arr[0] = "bb";
    cmd->arg_arr[1] = "-a";
    cmd->arg_arr[2] = NULL;
    cmd->fd_in = 0;
    cmd->fd_out = 0;
    cmd->name_file = NULL;
    cmd->token->builtin = NULL;
    cmd->next = NULL;
    cmd->path = "/bin/b";

    execute(cmd, env);
    free(cmd->arg_arr);
    free(cmd->token);
    free(cmd);

    return 0;
}