#include "../minishell.h"

int builtin_export(t_cmd *cmd, char **env)
{
    (void)cmd;
    while (*env++)
    {
        printf("%s\n", *env);
    }
    
    return (0);
}