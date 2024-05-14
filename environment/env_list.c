
#include "../minishell.h"

t_env	*lst_last(t_env *lst)
{
	t_env	*current;

	current = lst;
	if (lst == 0)
		return (0);
	while (current->next != 0)
		current = current->next;
	return (current);
}

t_env	*lst_new(char *name, char *value, t_env *new, int export)
{
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	if (!new->name || !new->value)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (NULL);
	}
	if (export == 1)
		new->export = 1;
	else
		new->export = 0;
	new->next = NULL;
	return (new);
}

void	lst_addback(t_env **list, t_env *new)
{
	t_env	*current;

	if (list)
	{
		if (*list == NULL)
			*list = new;
		else
		{
			current = lst_last(*(list));
			current->next = new;
		}
		new = NULL;
	}
}

t_env	*initialize_env_variables(t_env **head, char **env)
{
	int		i;
	char	*name;
	char	*value;
	t_env	*new;

	
	i = 0;
	while (env[i] != NULL)
	{
		name = ft_substr(env[i], 0, find_char(env[i]));
		value = getenv(name);
		new = lst_new(name, value ? value : "", new, 1);
		free(name);
		if (!new)
		{
			free_env_list(*head);
			return (NULL);
		}
		lst_addback(head, new);
		i++;
	}
	return (*head);
}
