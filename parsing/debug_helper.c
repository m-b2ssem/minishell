
#include "../minishell.h"

void	print_list(t_cmd **head)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = *head;
	while (cmd != NULL)
	{
		printf("Node: %s\n", cmd->args);
		tok = cmd->token;
		while (tok != NULL)
		{
			printf("\tTOK:%s\n", tok->string);
			printf("\tTYPE: %d\n", tok->type);
			//printf("\tJOIN: %d\n", tok->join);
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}

void	print_arr(t_cmd **cmd)
{
	t_cmd	*curr;
	int		i;

	curr = *cmd;
	i = 0;
	while (curr != NULL)
	{
		if (curr->arg_arr)
		{
			i = 0;
			while (curr->arg_arr[i])
			{
				printf("\t%s\n", curr->arg_arr[i]);
				i++;
			}
		}
		curr = curr->next;
	}
}
