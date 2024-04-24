#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include <sys/wait.h>


char* strjoin(const char* s1, const char* s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}



int main(int argc, char **argv, char **envp)
{
    char *command = "ls";
    char *path = get_bin_path(command);
    if (path == NULL)
    {
        printf("Command not found\n");
        return 1;
    }
    char *args[] = {path, "-a", NULL};
    int status;
    int pid = fork();
    if (pid == 0)
    {
        exit(1);
        return 10;
        execve(path, args, envp);
    }
    waitpid(pid, &status, 0);
    printf("status: %d\n", WEXITSTATUS(status));
    free(path);
    return 0;
}