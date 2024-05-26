#include "../minishell.h"

int	alloc_mem(char **name, char **value, const char *arg)
{
	*name = ft_calloc(sizeof(char), ft_strlen(arg) + 1);
	if (!*name)
		return (1);
	*value = ft_calloc(sizeof(char), ft_strlen(arg) + 1);
	if (!*value)
	{
		free(*name);
		return (1);
	}
	return (0);
}
