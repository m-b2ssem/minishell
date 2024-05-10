#include "../minishell.h"

int builtin_env(t_env *env)
{
    if (!env)
        return (1);
    printf("builtin_env\n");
    print_list_env(env);
    return (0);
}