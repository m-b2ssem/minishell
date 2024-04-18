#include <stdlib.h>
#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


typedef struct		s_cmd
{

	int				fd_in;
	int				fd_out;

	struct s_cmd	*next;
}           t_cmd;

int cmd_lenth(t_cmd *cmd)
{
    t_cmd   *cur;
    int     i;

    cur = cmd;
    i = 0;
    while (cur)
    {
        i++;
        cur = cur->next;
    }
    return (i);
}

/*int main(int argc, char **argv)
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
}*/

/*int main()
{
    int **fd;
    int     i;

    i = 5;
    fd = malloc(sizeof(int *) * 2);
    fd[i] = malloc(sizeof(int) * 2);
    if (!fd[i])
        return (5);
    if (pipe(fd[i]) == -1)
    {
        printf("error init the pipe");
        return (5);
    }
    if (i == 0)
    {
        printf("i is : %d\n", fd[i][0]);
 
    }
    printf("2 is : %d\n", fd[i][0]);
    return 0;
}*/

int free_pipe(int **pipefd)
{
    int i;

    i = 0;
    while (pipefd[i])
    {
        free(pipefd[i]);
        i++;
    }
    return (0);
}

int     setup_pipe(t_cmd *cmd, int **pipefd, int index)
{
    if (pipe(pipefd[index]) == -1)
    {
        printf("pipe error\n");
        return (6);
    }
    if (index == 0)
        cmd->fd_in = 0;
    else
        cmd->fd_in = pipefd[index - 1][0];
    if (cmd->next == NULL)
    {
        close(pipefd[index][0]);
        close(pipefd[index][1]);
        cmd->fd_out = 1;
    }
    else
        cmd->fd_out = pipefd[index][1];
    return (0);
}

int piping(t_cmd *cmd)
{
    t_cmd   *tmp;
    int     **pipefd;
    int     index;
    int     len;

    index = 0;
    tmp = cmd;
    len = cmd_lenth(cmd);
    pipefd = malloc(sizeof(int *) * (len + 1));
    if (!pipefd)
        return (5);
    pipefd[len] = NULL;
    while (tmp)
    {
        pipefd[index] = malloc(sizeof(int) * 2);
        if (!pipefd[index])
            return (5);
        if (setup_pipe(tmp, pipefd, index))
            return (free(pipefd[index]),free(pipefd), 6);
        tmp = tmp->next;
        index++;
    }
    free_pipe(pipefd);
    free(pipefd);
    return (0);
}

int main() {
    // Create some test commands
    t_cmd cmd1, cmd2, cmd3;
    cmd1.next = &cmd2;
    cmd2.next = &cmd3;
    cmd3.next = NULL;

    // Call the piping function
    int result = piping(&cmd1);

    // Check the result
    if (result == 0) {
        printf("Piping successful\n");
    } else {
        printf("Piping failed with error code %d\n", result);
    }

    return 0;
}