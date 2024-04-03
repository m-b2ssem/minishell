#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int random_char(void)
{

    char tmp[4];
    int c;
    int fd;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
        return (-1);
    if (read(fd, tmp, 4) != 4)
    {
        close(fd);
        return (-1);
    }
    close(fd);
    c = *((int*)tmp);
    if (c < 0)
        c = -c;
    c = c % 52;
    if (c < 26)
        return ('a' + c);
    else
        return ('A' + c - 26);
}

char *random_name(void)
{
    char    *file;
    int     i;
    int     c;

    i = 0;
    c = 0;
    file = malloc(sizeof(char) * 21);
    while (i < 20)
    {
        c = random_char();
        if (c == -1)
        {
            free(file);
            return (NULL);
        }
        file[i] = c;
        i++;
    }
    file[20] = '\0';
    return (file);
}

int heredoc(void)
{
    int     fd;
    char    *file;

    file = random_name();
    if (!file)
        return -1;

    fd = open(file, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        free(file);
        return -1;
    }

    write(fd, "hello word", 10);
    close(fd);
    free(file);
    return 0;
}

int main()
{

    int name = heredoc();
    printf("%d\n", name);
    return 0;
    
}