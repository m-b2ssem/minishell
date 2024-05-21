
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
			printf("\tTOK:-%s-\n", tok->string);
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

void	remove_blank_tokens(t_cmd *cmd)
{
	t_token	*current;
	t_token	*prev;
	t_token	*to_delete;

	to_delete = NULL;
	current = cmd->token;
	prev = NULL;
	while (current != NULL)
	{
		if (current->type == BLANK || current->type == NON)
		{
			to_delete = current;
			if (prev == NULL)
			{
				// If the BLANK token is the first token
				cmd->token = current->next;
			}
			else
			{
				// Bypass the BLANK token
				prev->next = current->next;
			}
			current = current->next;
			free(to_delete->string); // Assuming the string needs to be freed
			free(to_delete);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

// Function to remove BLANK tokens from all commands in the list
void	remove_blank_tokens_from_cmds(t_cmd **cmd_list)
{
	t_cmd	*curr_cmd;

	curr_cmd = *cmd_list;
	while (curr_cmd != NULL)
	{
		remove_blank_tokens(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
}
