#include "minishell.h"
void    execute(char *cml)
{
    redirections(cml);
}

int main(int argc,char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    (void)env;
    while (1)
    {
        char *input = readline("minishell> ");
        execute(input);
    }
    
    return 0;
}