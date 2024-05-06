#include "minishell.h"


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
    cmd->token->type = 4;
    cmd->token->str = "out";
    cmd->token->next = NULL;
    cmd->arg_arr = malloc(sizeof(char *) * 5);
    if (!cmd->arg_arr)
        return 5;
    cmd->arg_arr[0] = "ls";
    cmd->arg_arr[1] = "-l";
    cmd->arg_arr[2] = NULL;
    cmd->fd_in = 0;
    cmd->fd_out = 1;
    cmd->file = NULL;
    cmd->next = NULL;
    //cmd->path = "/bin/ls";

    /*cmd->next = malloc(sizeof(t_cmd));
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
    cmd->next->token->type = 0;
    cmd->next->token->type = 0;
    cmd->next->token->type = 0;
    cmd->next->token->type = 0;
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
    cmd->next->arg_arr[1] = "hello=";
    cmd->next->arg_arr[2] = NULL;
    cmd->next->fd_in = 0;
    cmd->next->fd_out = 1;
    cmd->next->file = NULL;
    cmd->next->next = NULL;
    //cmd->next->path = "/usr/bin/wc";*/
    
    execute(cmd, cmd->env);
    /*free(cmd->next->arg_arr);
    free(cmd->next->token);
    free(cmd->next);*/
    free_list(&cmd->env);
    free(cmd->arg_arr);
    free(cmd->token);
    free(cmd);

    return 0;
}