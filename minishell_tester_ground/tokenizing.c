
#include "minishell.h"

void iterate_through_cmd_args(t_cmd **line)
{
	t_cmd *current;

	current = *line;
	while (current != NULL)
	{

		current = current->next;
	}
}


