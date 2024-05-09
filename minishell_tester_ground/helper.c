
#include "minishell.h"

int	the_expander(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	char	*new;
	char	s1[] = " \"";
	char	s2[] = "\'";

	new = NULL;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string && curr_tok->string[0])
			{
				if (curr_tok->type == DELIM && curr_tok->expansion == 1)
				{
					if (curr_tok->string[0] == '"')
					{
						new = ft_strtrim(curr_tok->string, s1);
						printf("NEW STRING IS %s\n", new);
						// Put new string into token struct
					}
					else if (curr_tok->string[0] == '\'')
					{
						new = ft_strtrim(curr_tok->string, s2);
						printf("NEW STRING IS %s\n", new);
						// Put new string into token struct
					}
				}
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
