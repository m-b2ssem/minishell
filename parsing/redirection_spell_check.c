
#include "../minishell.h"

int	is_type_redir(t_token *tok)
{
	if (tok->type == HERE_DOC || tok->type == APPEND || tok->type == REDIR_IN
		|| tok->type == REDIR_OUT)
		return (1);
	return (0);
}

int	redirection_spell_check(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	int		redir;

	redir = 0;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (is_type_redir(curr_tok))
				redir = 1;
			else if (redir == 1 && curr_tok->string != 0
				&& curr_tok->string[0] != '\0')
			{
				if (is_type_redir(curr_tok) || curr_tok->type == BUILTIN)
					return (1);
				redir = 0;
			}
			curr_tok = curr_tok->next;
		}
		if (redir == 1)
			return (1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
