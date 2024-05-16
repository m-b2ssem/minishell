
#include "../minishell.h"

void	update_quote_strings(t_token *tok)
{
	char	s1[] = "\"";
	char	s2[] = "\'";
	char	*new;

	new = NULL;
	if (tok->string[0] == '"')
		new = ft_strtrim(tok->string, s1);
	else if (tok->string[0] == '\'')
		new = ft_strtrim(tok->string, s2);
	if (new == NULL)
		return ;
	if (new != tok->string)
	{
		free(tok->string);
		tok->string = ft_strdup(new);
		free(new);
	}
	if (tok->string == NULL)
		return ;
}

int	search_quotes_modify(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	char	*new;

	new = NULL;
	if (line == NULL)
		return (1);
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->string[0])
			{
				if (curr_tok->type == D_QUOTE || curr_tok->type == S_QUOTE)
					update_quote_strings(curr_tok);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
