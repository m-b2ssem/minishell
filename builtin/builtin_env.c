#include "../minishell.h"

int builtin_env(char **env)
{
    int i;

    i = 0;
    if (!env)
        return (1);
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}