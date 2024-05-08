
#include "minishell.h"

// Handling here_docs
// if HERE_DOC is last token then SYNTAX ERROR
// if HERE_DOC followed by DQUOTES or SQUOTES (len == 2)
// Exit with an empty line;
// if HEREDOC vor ARG/DQUOTE/SQUOTE is correct
// Trim Quotes depending on dominant quote.
// make it DELIMITER

// cat <<"hello" hell
// if there is an arg after the EOF of the heredoc,
// the question is if the file/directory exists or not
// EXIT: cat: hello: No such file or directory

// when working with pipe, there is one extra token - which i took maybe use??

// [CMD]
// the cmd before the heredoc can be any cmd that accepts input from standard input
// the delimiter has to match the exact word in the heredoc

int	is_type_redir(t_token *tok)
{
	if (tok->type == HERE_DOC || tok->type == APPEND || tok->type == REDIR_IN
		|| tok->type == REDIR_OUT)
		return (1);
	return (0);
}

int	check_correct_heredoc_usage(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	int		heredoc;

	heredoc = 0;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->type == HERE_DOC)
				heredoc = 1;
			else if (heredoc == 1 && curr_tok->string != 0
				&& curr_tok->string[0] != '\0')
			{
				if (is_type_redir(curr_tok))
				{
					printf("Wrong handling of heredoc\n");
					exit(1);
				}
				else if (curr_tok->type == D_QUOTE || curr_tok == S_QUOTE)
				{
					curr_tok->expansion = 0;
					curr_tok->type = DELIM;
					heredoc = 0;
					printf("changed type of arg after heredoc\n");
				}
				// printf("Stuff after heredoc encountered\n");
			}
			// else
			// printf("Nothing\n");
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	if (heredoc == 1)
		printf("stand alone heredoc\n");
	return (0);
}

// if DELIM with
