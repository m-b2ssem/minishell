
#include "../minishell.h"

int	free_list(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	return (0);
}

void	free_list_tokens(t_token **head)
{
	t_token	*current;
	t_token	*tmp;

	current = *head;
	while (current->next != NULL)
	{
		tmp = current;
		free(tmp->string);
		current = current->next;
	}
	*head = NULL;
}

void	free_everything(t_cmd **line)
{
	t_cmd	*current;
	t_cmd	*tmp;

	current = *line;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->args)
			free(tmp->args);
		if (tmp->arg_arr)
			free(tmp->arg_arr);
		if (tmp->token)
			free_list_tokens(&tmp->token);
		free(tmp);
	}
	*line = NULL;
}
