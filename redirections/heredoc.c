#include "../minishell.h"

extern sig_atomic_t g_signal;

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

char *my_getenv(char *name, t_env *env)
{
    t_env *tmp;

    tmp = env;
    int len = strlen(name);
    while (tmp->next != NULL)
    {
        if (strncmp(tmp->name, name, len) == 0 &&  tmp->export == 1)
        {
            return (tmp->value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

char   *check_for_env_value(char *str, t_env *env, t_token *tok)
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
            after_doller = malloc(sizeof(char) * (strlen(str) + 1));
            if (!after_doller)
                return (free(new_str), NULL);
            while (str[i] != '\0' && str[i] != ' ')
            {
                after_doller[k++] = str[i++];
            }
            after_doller[k] = '\0';
            var_value = my_getenv(after_doller, env);
            if (var_value && tok->expansion == 0)
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


int write_inside_file(t_cmd *cmd, char *word, int fd, t_token *tok)
{
    char    *str;

    str = NULL;
    while (1)
    {
        str = readline(">");
        if (str == NULL || g_signal == 130)
        {
            g_signal = 0;
            return (-1);
        }
        if (strcmp(word, str) == 0)
            break;
        if (str != NULL)
        {
            str = check_for_env_value(str, cmd->env, tok);
        }
        write(fd, str, strlen(str));
        write(fd, "\n", 1);
        free(str);
    }
    free(str);
    return (0);
}


int heredoc(t_cmd *cmd, char *word, t_token *tok)
{
    int fd;
    char *file;

    file = random_name();
    if (!file)
        return -1;
    fd = open(file, O_CREAT | O_RDWR, 0644);
    if (fd == -1)
        return(free(file), -1);
    heredoc_signals();
    write_inside_file(cmd, word, fd, tok);
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return(free(file), -1);
    cmd->fd_in = fd;
    if (unlink(file) == -1)
    {
        ft_putstr_fd("there is an error deleting the file\n", 2);
        return(-1);
    }
    cmd->file = file;
    return (fd);
}
