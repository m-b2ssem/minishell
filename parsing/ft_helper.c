
#include "../minishell.h"

void	print_list(t_cmd **head)
{
	t_cmd	*cmd;
	t_token	*tok;

	cmd = *head;
	if (head == NULL)
	{
		printf("Head\n");
		return ;
	}
	// if (head)
	// {
	// 	int d = cmd_lenth(cmd);
	// 	printf("Head %d\n", d);
	// 	return ;
	// }
	while (cmd != NULL)
	{
		printf("Node: %s\n", cmd->args);
		tok = cmd->token;
		while (tok != NULL)
		{
			printf("\tTOK:%s\n", tok->string);
			printf("\tTYPE: %d\n", tok->type);
			printf("\tJOIN: %d\n", tok->join);
			// printf("\tEXPANSION: %d\n", tok->expansion);
			tok = tok->next;
		}
		cmd = cmd->next;
	}
}
