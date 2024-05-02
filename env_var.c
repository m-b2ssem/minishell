
#include "minishell.h"

void	print_list(t_env *head) // Single pointer to head
{
	t_env *current = head;

	printf("HERE\n");
	while (current != NULL)
	{
		printf("    Name: %s\n", current->name);
		printf("    Value: %s\n", current->value);
		current = current->next; // Move to the next node
	}
	printf("NULL\n");
}

t_env	*lst_last(t_env *lst)
{
	t_env	*current;

	current = lst;
	if (lst == 0)
		return (0);
	while (current->next != 0)
	{
		current = current->next;
	}
	return (current);
}

t_env	*lst_new(char *name, char *value, t_env *new)
{
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = ft_strdup(name);
	// printf("---> %s\n", new->name);
	new->value = ft_strdup(value);
	// printf("---> %s\n", new->value);
	if (!new->name || !new->value)
	{
		free(new->name);
		free(new->value);
		free(new);
		return (NULL);
	}
	new->export = 1;
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

int	find_char(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}

void	initialize_env_variables(t_env **head, char **env)
{
	int		i;
	int		flag;
	char	*name;
	char	*value;
	t_env	*new;

	i = 0;
	while (env[i] != NULL)
	{
		name = ft_substr(env[i], 0, find_char(env[i]));
		value = getenv(name);
		new = lst_new(name, value ? value : "", new);
		if (!new)
		{
			free(name);
			return ;
		}
		lst_addback(head, new);
		free(name);
		i++;
	}
}
void	free_list(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}

// int	main(int argc, char **argv, char **env)
// {
// 	extern char	**__environ;
// 	t_env		*var;

// 	var = NULL;
// 	env = __environ;
// 	(void)argc;
// 	(void)argv;
// 	initialize_env_variables(&var, env);
// 	print_list(var);
// 	free_list(var);
// 	return (0);
// }
