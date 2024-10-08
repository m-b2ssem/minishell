#include "../minishell.h"

static	void	free_variable(t_env *curr)
{
	free(curr->name);
	free(curr->value);
	free(curr);
}

int	builtin_unset(t_env **head, t_cmd *cmd)
{
	t_env	*prev;
	t_env	*curr;
	int		i;

	i = 0;
	prev = NULL;
	while (cmd->arg_arr[i] != NULL)
	{
		curr = *head;
		while (curr != NULL)
		{
			if (ft_strcmp(curr->name, cmd->arg_arr[i]) == 0)
			{
				if (prev == NULL)
					*head = curr->next;
				else
					prev->next = curr->next;
				free_variable(curr);
			}
			prev = curr;
			curr = curr->next;
		}
		i++;
	}
	return (0);
}
