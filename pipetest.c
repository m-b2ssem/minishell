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

        char *newargv[] = {  "/bin/rm","hi", NULL };
        execve(newargv[0], newargv, NULL);
    }
    waitpid(pid1, NULL, 0);
    return 0;
}