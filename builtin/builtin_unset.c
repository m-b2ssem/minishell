#include "../minishell.h"

int builtin_unset(t_cmd *cmd, char *unset)
{
    char **new_env;
    char    **curr_env;
    int     i;
    int     j;

    i = 0;
    j = 0;
    curr_env = cmd->env;
    while(curr_env[i])
        i++;
    new_env = (char **)malloc(sizeof(char *) * (i + 1));
    if (!new_env)
    {
        printf("can't allocate memory!");
        return (1);
    }
    i = 0;
    while (curr_env[i])
    {
        if (ft_strncmp(unset, curr_env[i], ft_strlen(unset)) != 0)
        {
            new_env[j] = curr_env[i];
            j++;
        }
        i++;
    }
    new_env[j] = NULL;
    cmd->env = new_env; // set it back to the env
    // for testing
    /*i = 0;
    while (new_env[i] != NULL)
    {
        printf("%s\n", new_env[i]);
        i++;
    }*/
    return (0);
}