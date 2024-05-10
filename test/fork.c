#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
// int main(int argc, char const *argv[])
// {
//     pid_t *id;

//     id = malloc(sizeof(pid_t) * 4);
//     id[3] = NULL;
//     id[0] = fork();
//     if (id[0] == 0)
//     {
//         printf("I am the child process\n");
//     }
//     else
//     {
//         printf("I am the parent process\n");
//     }
//     return 0;
// }
