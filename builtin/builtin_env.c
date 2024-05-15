#include "../minishell.h"

int builtin_env(t_env *env)
{
    if (!env)
        return (1);
    while (env)
    {
        if (env->export == 1)
        {
            printf("%s=%s\n", env->name, env->value);
        }
        if (env->export == 0)
        {
            printf("%s=\n", env->name);
        }
        env = env->next;
    }
    return (0);
}