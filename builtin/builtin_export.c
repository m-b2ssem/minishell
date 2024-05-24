#include "../minishell.h"

t_env	*copy_env_list(t_env *env)
{
	t_env	*new_env;
	t_env	*temp;

	if (env->next == NULL)
		return (NULL);
	new_env = NULL;
	while (env != NULL)
	{
		temp = (t_env *)malloc(sizeof(t_env));
		if (!temp)
			return (free_list(&new_env), NULL);
		if (env->name)
			temp->name = ft_strdup(env->name);
		else
			temp->name = ft_strdup(" ");
		if (env->value)
			temp->value = ft_strdup(env->value);
		else
			temp->value = ft_strdup(" ");
		temp->export = env->export;
		temp->next = new_env;
		new_env = temp;
		env = env->next;
	}
	return (new_env);
}

void	bubble_sort(t_env **head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	swapped = 1;
	if (*head == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *head;
		while (ptr1->next != lptr)
		{
			if (strcmp_custom(ptr1->name, ptr1->next->name) > 0)
			{
				swap(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

int	return_value(char *arg, char **value)
{
	int	i;
	int	j;
	int	export;

	i = 0;
	j = 0;
	export = 0;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	if (arg[i] == '\0')
	{
		(*value)[j] = ' ';
		(*value)[j + 1] = '\0';
		return (export);
	}
	if (arg[i] == '=')
	{
		export = 1;
		i++;
	}
	while (arg[i] != '\0')
		(*value)[j++] = arg[i++];
	(*value)[j] = '\0';
	return (export);
}

int	add_variable(t_cmd *cmd)
{
	int		i;
	int		export;
	char	*name;
	char	*value;
	t_env	*new;

	i = 1;
	name = NULL;
	value = NULL;
	name = ft_calloc(sizeof(char), (ft_strlen(cmd->arg_arr[1]) + 1));
	if (!name)
		return (1);
	value = ft_calloc(sizeof(char), (ft_strlen(cmd->arg_arr[1]) + 1));
	if (!value)
		return (free(name), 1);
	while (cmd->arg_arr[i] != NULL)
	{
		return_name(cmd->arg_arr[i], &name);
		export = return_value(cmd->arg_arr[i], &value);
		if (search_if_variable_exist(cmd, name))
			update_value(cmd, name, value, export);
		else
		{
			new = lst_new(name, value, new, export);
			if (!new)
				return (free(name), free(value), 1);
			lst_addback(&cmd->env, new);
		}
		i++;
	}
	return (free(name), free(value), 0);
}

int	builtin_export(t_cmd *cmd)
{
	t_env	*temp;
	t_env	*head;

	temp = NULL;
	head = NULL;
	if (export_checker(cmd))
		return (1);
	if (cmd->arg_arr[1] != NULL)
	{
		if (add_variable(cmd))
			return (1);
		return (0);
	}
	temp = copy_env_list(cmd->env);
	if (!temp)
		return (1);
	head = temp;
	bubble_sort(&temp);
	print_export(temp);
	free_list(&head);
	return (0);
}
