
#include "../minishell.h"

int	token_type_builtin(char *s)
{
	if (ft_strcmp("cd", s) == 0)
		return (1);
	else if (ft_strcmp("echo", s) == 0)
		return (1);
	else if (ft_strcmp("pwd", s) == 0)
		return (1);
	else if (ft_strcmp("export", s) == 0)
		return (1);
	else if (ft_strcmp("unset", s) == 0)
		return (1);
	else if (ft_strcmp("env", s) == 0)
		return (1);
	else if (ft_strcmp("exit", s) == 0)
		return (1);
	return (0);
}

void	token_type(t_token *tok)
{
	if (token_type_builtin(tok->string))
		tok->type = BUILTIN;
	else if (tok->string[0] == '<' && tok->string[1] == '\0')
		tok->type = REDIR_IN;
	else if (tok->string[0] == '>' && tok->string[1] == '\0')
		tok->type = REDIR_OUT;
	else if (tok->string[0] == '<' && tok->string[1] == '<'
		&& tok->string[2] == '\0')
		tok->type = HERE_DOC;
	else if (tok->string[0] == '>' && tok->string[1] == '>'
		&& tok->string[2] == '\0')
		tok->type = APPEND;
	else if (tok->string[0] == '"' && tok->string[ft_strlen(tok->string)
		- 1] == '"')
		tok->type = D_QUOTE;
	else if (tok->string[0] == '\'' && tok->string[ft_strlen(tok->string)
		- 1] == '\'')
		tok->type = S_QUOTE;
	else if (tok->string[0] == ' ' && tok->string[1] == '\0')
		tok->type = BLANK;
	else if (ft_strlen(tok->string) != 0 && tok->type == NON)
		tok->type = ARG;
	else
		tok->type = NON;
}

int	decide_token_type(t_cmd **line)
{
	t_cmd	*curr;
	t_token	*tok;

	if (line == NULL)
		return (1);
	curr = *line;
	while (curr != NULL)
	{
		tok = curr->token;
		while (tok != NULL)
		{
			token_type(tok);
			tok = tok->next;
		}
		curr = curr->next;
	}
	return (0);
}
