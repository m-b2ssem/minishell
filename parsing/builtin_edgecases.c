
#include "../minishell.h"

void	builtin_bridge(t_token *tok)
{
	if (ft_strcmp(tok->string, "exit"))

}

int	builtin_edgecase(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;
	t_token	*prev;

	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_token = curr_cmd->token;
		prev = NULL;
		while (curr_token != NULL)
		{
			if (curr_token->string != NULL && curr_token->string[0] != '\0' && prev->type == BUILTIN)
			{
				if 
			}
			prev = curr_token;
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
