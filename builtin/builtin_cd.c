#include "../minishell.h"

int cd(char *new_path)
{
    if (new_path == NULL)
    {
        printf("no dirctory with this name\n");
        return (1);
    }
    if (chdir(new_path) != 0)
    {
        printf("no dirctory with this name\n");
        return (1);
    }
    return (0);
}