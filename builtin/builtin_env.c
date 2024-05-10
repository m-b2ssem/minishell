#include "../minishell.h"

int builtin_env(t_env *env)
{
    if (!env)
        return (1);
    print_list(env);
    return (0);
}