#include "minishell.h"

void    execute(char *cml)
{

    if (cml != NULL)
    {
        cd(cml);
        builtin_pwd();
    }
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