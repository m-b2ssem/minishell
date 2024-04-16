#include <stdio.h>
#include <unistd.h>
#include <string.h>

char *my_getenv(char *name, char **env)
{
    int i = 0;
    int len = strlen(name);
    while (env[i])
    {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            return &env[i][len + 1];
        }
        i++;
    }
    return NULL;
}

int main(int argc, char **argv, char **env)
{
    char *val;

    val = my_getenv("USER", env);
    printf("thisis the value %s\n", val);
    return 0;
}