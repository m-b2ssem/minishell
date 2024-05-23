
#include "../minishell.h"

t_cmd	*arg_last(t_cmd *lst)
{
	t_cmd	*current;

	current = lst;
	if (lst == NULL)
		return (NULL);
	while (current->next != 0)
	{
		current = current->next;
	}
	return (current);
}

void	arg_add_back(t_cmd **stack, t_cmd *new)
{
	t_cmd	*current;

	current = *stack;
	if (stack)
	{
		if (*stack == NULL)
			*stack = new;
		else
		{
			current = arg_last(*(stack));
			current->next = new;
		}
		new = NULL;
	}
}

void	init_node(t_cmd *new, t_env *list)
{
	new->token = NULL;
	new->env = list;
	new->args = NULL;
	new->arg_arr = NULL;
	new->file = NULL;
	new->path = NULL;
	new->next = NULL;
	new->fd_in = 0;
	new->fd_out = 0;
}

t_cmd	*init_new_node(char *arr, t_cmd *new, t_env *env)
{
	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		free(arr);
		return (NULL);
	}
	init_node(new, env);
	new->args = ft_strdup(arr);
	if (new->args == NULL)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int	initialize_arguments(t_cmd **line, char **user, t_env *env)
{
	t_cmd	*new;
	int		i;

	new = NULL;
	i = -1;
	if (user == NULL)
		return (1);
	while (user[++i])
	{
		new = init_new_node(user[i], new, env);
		if (new == NULL)
		{
			while (user[i]) // Free remaining user elements in case of failure
			{
				free(user[i]);
				--i;
			}
			free(user);
			return (1);
		}
		free(user[i]);
		arg_add_back(line, new);
	}
	free(user);
	return (0);
}
