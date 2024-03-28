#include "../minishell.h"

int    builtin_pwd()
{
    char    *pwd;

    if ((pwd = getcwd(NULL, 0)) != NULL)
    {
        printf("%s\n", pwd);
    }
    else
    {
        return (1);
    }
    free(pwd);
    return (0);
}