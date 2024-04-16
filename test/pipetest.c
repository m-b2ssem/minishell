#include <stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
    int fd[2];

    char *str = argv[1];
    if (pipe(fd) == -1)
    {
        return 5;
    }

    int pid1 = fork();
    if (pid1 < 0)
    {
        printf("error init the child procces");
    }
    if (pid1 == 0)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        char *newargv[] = {  "/bin/ls", NULL, NULL };
        execve(newargv[0], newargv, NULL);
    }
    int pid2 = fork();
    if (pid2 < 0)
    {
        printf("error init the child procces");
    }
    if (pid2 == 0)
    {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        char *newargv[] = {  "/bin/wc", "-l", NULL };
        execve(newargv[0], newargv, NULL);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    return 0;
}