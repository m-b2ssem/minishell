#include "../minishell.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char *search_paths(char **paths, char *command)
{
    char *bin_path;
    char *tmp;
    int i = 0;

    while (paths[i] != NULL)
    {
        bin_path = ft_strjoin(paths[i], "/");
        if (bin_path == NULL)
            return (free_paths(paths), NULL);
        tmp = ft_strjoin(bin_path, command);
        if (tmp == NULL)
            return (free_paths(paths), free(bin_path), NULL);
        if (access(tmp, F_OK) == 0)
        {
            free(bin_path);
            free_paths(paths);
            return (tmp);
        }
        free(bin_path);
        free(tmp);
        i++;
    }
    free_paths(paths);
    return (NULL);
}
char *get_path(char *command, t_env *env)
{
    char *path;
    char **paths;

    if (command && (command[0] == '.' || command[0] == '/'))
        return (command);
    path = my_getenv("PATH", env); // us my my_getenv
    if (path == NULL)
        return (NULL);
    paths = ft_split(path, ':');
    if (paths == NULL)
        return (NULL);
    return (search_paths(paths, command));
}

int	cmd_lenth(t_cmd *cmd)
{
	t_cmd	*cur;
	int		i;

	cur = cmd;
	i = 0;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}
