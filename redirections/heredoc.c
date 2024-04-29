#include "../minishell.h"

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
    file = malloc(sizeof(char) * 31);
    if (!file)
        return (NULL);
    while (i < 30)
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
    file[30] = '\0';
    return (file);
}

char *my_getenv(char *name, char **env)
{
    int i = 0;
    int len = strlen(name);
    while (env[i])
    {
        if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
        {
            return (&env[i][len + 1]);
        }
        i++;
    }
    return (NULL);
}

char   *check_for_env_value(char *str, char **env)
{
    char    *new_str;
    char    *after_doller;
    char    *var_value;
	int		i = 0;
    int     j = 0;
    int     k = 0;

    new_str = malloc(sizeof(char) * (strlen(str) + 1));
    if (!new_str)
    {
        return (NULL);
    }
	while (str[i])
	{
		if (str[i] != '$')
		{
            new_str[j++] = str[i++];
		}
        else
        {
            i++;
            after_doller = malloc(sizeof(char *) * (strlen(str) + 1));
            if (!after_doller)
                return (NULL);
            while (str[i] != '\0' && str[i] != ' ')
            {
                after_doller[k++] = str[i++];
            }
            after_doller[k] = '\0';
            var_value = my_getenv(after_doller, env);
            if (var_value)
            {
                strcpy(&new_str[j], var_value); // replace $word with its value
                j += strlen(var_value);
            }
            else
            {
                new_str[j++] = '$'; // keep $word as is
                strcpy(&new_str[j], after_doller);
                j += k;
            }
            free(after_doller);         
        }
	}
    new_str[j] = '\0';
	free(str);
	return (new_str);
}


int write_inside_file(t_cmd *cmd, char *path, int fd)
{
    char    *str;

    (void)cmd;
    str = NULL;
    while (1)
    {
        str = readline(">");
        if (str == NULL)
        {
            return (-1);
        }
        if (strcmp(path, str) == 0)
            break;
        if (str != NULL)
        {
            str = check_for_env_value(str, cmd->env);
        }
        write(fd, str, strlen(str));
        write(fd, "\n", 1);
        free(str);
    }
    free(str);
    return (0);
}


int heredoc(t_cmd *cmd, t_token *token)
{
    int fd;
    char *file;
    char buffer[1024];
    ssize_t bytesRead;

    file = random_name();
    if (!file)
        return -1;

    fd = open(file, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        free(file);
        return (-1);
    }
    // this is to write inside the file 
    write_inside_file(cmd ,token->path, fd);
    close(fd);

    fd = open(file, O_RDONLY);
    if (fd == -1) {
        free(file);
        return (-1);
    }
    // this is will write from the file to the stdin
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDIN_FILENO, buffer, bytesRead);
    }
    close(fd);
    if (unlink(file) == -1)
    {
        printf("there is an error deleting the file\n");
        return(-1);
    }
    free(file);
    return (fd);
}