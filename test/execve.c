#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        printf("pipe error\n");
        return (6);
    }
    int fd_in = STDIN_FILENO;
    int fd_out = pipefd[1];
    int fd_in2 = pipefd[0];
    int fd_out2 = STDOUT_FILENO;
    char *args[] = {"/bin/ls", "-a", NULL};
    execve("/bin/ls", args, env);
    char *args2[] = {"/usr/bin/wc", "-l", NULL};
    execve("/usr/bin/wc", args2, env);
    return 0;
}