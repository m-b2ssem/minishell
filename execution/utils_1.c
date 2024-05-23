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

static char	*search_path_2(char *command, char **paths)
{
	char	*tmp;
	int		i;

	if (command[0] == '.' || command[1] == '/')
		return (command);
	if (access(command, F_OK) == 0)
		return (free_paths(paths), command);
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], command);
		if (tmp == NULL)
			return (free_paths(paths), NULL);
		if (access(tmp, F_OK) == 0)
		{
			free_paths(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_paths(paths);
	printf_error(command);
	return (NULL);
}

static char	*search_paths(char **paths, char *command)
{
	char	*bin_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		bin_path = ft_strjoin(paths[i], "/");
		if (bin_path == NULL)
			return (free_paths(paths), NULL);
		tmp = ft_strjoin(bin_path, command);
		if (tmp == NULL)
			return (free_paths(paths), free(bin_path), NULL);
		if (access(tmp, F_OK) == 0)
			return (free(bin_path), free_paths(paths), tmp);
		free(bin_path);
		free(tmp);
		i++;
	}
	printf_error(command);
	free_paths(paths);
	return (NULL);
}

char	*get_path(char *command, t_env *env)
{
	char	*path;
	char	**paths;

	if (command == NULL)
		return (NULL);
	path = my_getenv("PATH", env);
	if (path == NULL)
		return (printf_error(command), NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	if (command && (command[0] == '.' || command[0] == '/'))
		return (search_path_2(command, paths));
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
