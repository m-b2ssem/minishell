
#include "../minishell.h"

int	is_type_arg(t_token *tok)
{
	if (tok->type == ARG || tok->type == D_QUOTE || tok->type == S_QUOTE)
		return (1);
	return (0);
}

void	change_redir_relation(t_token *tok, int *redir)
{
	if (is_type_arg(tok))
	{
		if (*redir == 5)
		{
			if (tok->type == ARG)
				tok->expansion = 0;
			else
				tok->expansion = 1;
			tok->type = DELIM;
		}
		else if (*redir == 6)
			tok->type = A_FILE;
		else if (*redir == 7)
			tok->type = INFILE;
		else if (*redir == 8)
			tok->type = OUTFILE;
		*redir = 0;
	}
}

void	change_redirection_relation(t_token *tok, int *redir)
{
	if (tok->type == HERE_DOC)
		*redir = 5;
	else if (tok->type == APPEND)
		*redir = 6;
	else if (tok->type == REDIR_IN)
		*redir = 7;
	else if (tok->type == REDIR_OUT)
		*redir = 8;
	else
		*redir = 0;
}

int	redirection_usage(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	int		redir;

	curr_cmd = *line;
	redir = 0;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (is_type_redir(curr_tok))
				change_redirection_relation(curr_tok, &redir);
			else if (redir > 0 && curr_tok->string != 0
				&& curr_tok->string[0] != '\0' && join_quoted_helper(curr_tok))
				change_redir_relation(curr_tok, &redir);
			curr_tok = curr_tok->next;
		}
		if (redir > 0)
			return (1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
