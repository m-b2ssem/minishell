#include "minishell.h"

int exit_status;

int main(int argc,char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return 1;
    cmd->token = (t_token *)malloc(sizeof(t_token));
    if (!cmd->token) {
        free(cmd);
        return 1;
    }

    /*cmd->env = malloc(sizeof(t_env));
    if (!cmd->env) {
        free(cmd->token);
        free(cmd);
        return 1;
    }*/
    cmd->env = NULL;
    initialize_env_variables(&cmd->env, env);
    // Initialize all fields
    cmd->token->type.REDIR_DIN = 0;
    cmd->token->type.REDIR_IN = 0;
    cmd->token->type.REDIR_OUT = 0;
    cmd->token->type.REDIR_DOUT = 0;
    cmd->token->path = NULL;
    cmd->token->next = NULL;
    cmd->arg_arr = malloc(sizeof(char *) * 5);
    if (!cmd->arg_arr)
        return 5;
    cmd->arg_arr[0] = "export";
    cmd->arg_arr[1] = "hello=word";
    cmd->arg_arr[2] = NULL;
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    cmd->name_file = NULL;
    cmd->token->builtin = "export";
    cmd->next = NULL;
    //cmd->path = "/bin/ls";

    cmd->next = malloc(sizeof(t_cmd));
    if (!cmd->next) {
        free(cmd);
        return 1;
    }
    cmd->next->next = NULL;
    cmd->next->token = (t_token *)malloc(sizeof(t_token));
    if (!cmd->next->token) {
        free(cmd->next);
        free(cmd);
        return 1;
    }
    cmd->next->token->type.REDIR_DIN = 0;
    cmd->next->token->type.REDIR_IN = 0;
    cmd->next->token->type.REDIR_OUT = 0;
    cmd->next->token->type.REDIR_DOUT = 0;
    cmd->next->token->path = NULL;
    cmd->next->token->next = NULL;
    cmd->next->env = cmd->env;
    cmd->next->arg_arr = malloc(sizeof(char *) * 3);
    if (!cmd->next->arg_arr) {
        free(cmd->next->token);
        free(cmd->next);
        free(cmd);
        return 5;
    }
    cmd->next->arg_arr[0] = "export";
    cmd->next->arg_arr[1] = NULL;
    cmd->next->arg_arr[2] = NULL;
    cmd->next->fd_in = 0;
    cmd->next->fd_out = 1;
    cmd->next->name_file = NULL;
    cmd->next->token->builtin = "export";
    cmd->next->next = NULL;
    //cmd->next->path = "/usr/bin/wc";
    
    execute(cmd, cmd->env);
    print_list(cmd->next->env);
    free(cmd->next->arg_arr);
    free(cmd->next->token);
    free(cmd->next);
    free_list(&cmd->env);
    free(cmd->arg_arr);
    free(cmd->token);
    free(cmd);

    return 0;
}