
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {

    int i = fork();
    if (i == 0)
    {
        struct stat fileStat;
        const char *filename = "x";
        char *argv[] = {"rm", "x", NULL};
        execve("/bin/hh", argv, envp);
        if (stat(filename, &fileStat) == 0) {
            if (fileStat.st_mode == 33152)
                printf("Permissions deneid\n");
            else
                printf("Faile to e exitcute the file\n");
            int b = fileStat.st_mode;
            printf("File Permissions: %d\n", b);
            printf("File size: %lld bytes\n", fileStat.st_size);
            printf("Permissions: %o\n", fileStat.st_mode & 0777);
            // You can access more information like modification time, etc., through other members of the `fileStat` structure.
        } else {
            perror("here");
        }
    }
    waitpid(i, NULL, 0);
    return 0;
}