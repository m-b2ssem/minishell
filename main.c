#include "minishell.h"

int parse_cmd(char *str, t_cmd **line)
{

    //attach the address of env ölist to cmd
    char **arr;
    int res;

        res = check_for_unclosed_quotes(str);
		if (res != 0)
		{
			printf("Result %d\n", res);
			printf("Unclosed detected\n");
		}
		else
		{
			arr = ft_split_cmd(str, '|');
			initialize_arguments(line, arr);
			iterate_through_cmd_args(line);
			decide_token_type(line);
			if (redirection_spell_check(line) == -1)
			{
				printf("Syntax error in redirection\n");
			}
			if (heredoc_usage(line) == -1)
			{
				printf("WRONG__________\n");
			}
			//print_list(line);
			// the_expander(&line);
			organise_arg(line);
        }
    return (0);
}

void free_list_tokens(t_token **head)
{
    t_token *current;
    t_token *tmp;

    current = *head;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;
        free(tmp->string);
        free(tmp);
    }
    *head = NULL;
}


void free_everything(t_cmd **line)
{
    t_cmd *current;
    t_cmd *tmp;

    current = *line;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;
        free(tmp->args);
        free(tmp->arg_arr); 
        free_list_tokens(&tmp->token);
        free(tmp);
    }
    *line = NULL;
}



int	main(int argc, char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    int status;
    char *str;
    t_cmd *cmd = NULL;
    t_env **envp = NULL;
    (void)env;
    (void)envp;

    status = 0;
    initialize_env_variables(envp, env);
    while (1)
    {
        str = readline("minishell> ");
        if (str == NULL)
        {
            return (0);
            //free_everything_exit(cmd);
        }
        add_history(str);
        parse_cmd(str, &cmd);
        print_list(&cmd);
        status = execute(&cmd, cmd->env);
        printf("Status: %d\n", status);
        free_everything(&cmd);
    }
    return (0);
}
