
#include "../minishell.h"

int	update_quote_strings(t_token *tok)
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
		return (1);
	if (new != tok->string)
	{
		free(tok->string);
		tok->string = new;
	}
	if (tok->string == NULL)
		return (1);
	return (0);
}

int	search_quotes_modify(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;

	if (line == NULL)
		return (1);
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->string[0] != '\0')
			{
				if (curr_tok->type == D_QUOTE || curr_tok->type == S_QUOTE)
					if (update_quote_strings(curr_tok) > 0)
						return (1);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
