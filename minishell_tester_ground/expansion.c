
// Handling here_docs
// if HERE_DOC is last token then SYNTAX ERROR
// if HERE_DOC followed by DQUOTES or SQUOTES (len == 2)
// Exit with an empty line;
// if redir vor ARG/DQUOTE/SQUOTE is correct
// Trim Quotes depending on dominant quote.
// make it DELIMITER

// cat <<"hello" hell
// if there is an arg after the EOF of the redir,
// the question is if the file/directory exists or not
// EXIT: cat: hello: No such file or directory

// when working with pipe, there is one extra token - which i took maybe use??

// [CMD]
// the cmd before the redir can be any cmd that accepts input from standard input
// the delimiter has to match the exact word in the redir

#include "minishell.h"

int	is_type_redir(t_token *tok)
{
	if (tok->type == HERE_DOC || tok->type == APPEND || tok->type == REDIR_IN
		|| tok->type == REDIR_OUT)
		return (1);
	return (0);
}

// int	is_possible_eof(t_token *tok)
// {
// 	if (tok->type == ARG || tok->type == D_QUOTE || tok->type == S_QUOTE)
// }

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
					return (-1);
			}
			curr_tok = curr_tok->next;
		}
		if (redir == 1)
			return (-1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

int	is_type_arg(t_token *tok)
{
	if (tok->type == ARG || tok->type == D_QUOTE || tok->type == S_QUOTE)
		return (1);
	return (0);
}

void	change_redir_relation(t_token *tok, int *redir)
{
	if (*redir == 5 && is_type_arg(tok))
	{
		if (tok->type == ARG)
		{
			tok->type = DELIM;
			tok->expansion = 1;
		}
		else if (tok->type == D_QUOTE || tok->type == S_QUOTE)
		{
			tok->type = DELIM;
			tok->expansion = 0;
		}
	}
	else if (*redir == 6 && is_type_arg(tok))
	{
		if (tok->type == ARG)
		{
			tok->type = A_FILE;
			tok->expansion = 1;
		}
		else if (tok->type == D_QUOTE || tok->type == S_QUOTE)
		{
			tok->type = A_FILE;
			tok->expansion = 0;
		}
	}
	else if (*redir == 7 && is_type_arg(tok))
	{
		if (tok->type == ARG || tok->type == D_QUOTE || tok->type == S_QUOTE)
		{
			tok->type = INFILE;
			tok->expansion = 1;
		}
	}
	else if (*redir == 8 && is_type_arg(tok))
	{
		if (tok->type == ARG || tok->type == D_QUOTE || tok->type == S_QUOTE)
		{
			tok->type = OUTFILE;
			tok->expansion = 1;
		}
	}
	*redir = 0;
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

int	heredoc_usage(t_cmd **line)
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
				&& curr_tok->string[0] != '\0')
				change_redir_relation(curr_tok, &redir);
			curr_tok = curr_tok->next;
		}
		if (redir > 0)
			return (-1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
