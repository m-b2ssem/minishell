
#include "minishell.h"

void	init_node_tokens(t_token *new)
{
	new->string = NULL;
	new->expansion = 0;
	new->next = NULL;
	new->type = NON;
}

t_token	*new_token(char *arg, t_token *new)
{
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	init_node_tokens(new);
	new->string = ft_strdup(arg);
	if (new->string == NULL)
		return (NULL);
	return (new);
}

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
	else if (tok->string[0] == '<' && tok->string[1] == '<')
		tok->type = HERE_DOC;
	else if (tok->string[0] == '>' && tok->string[1] == '>')
		tok->type = APPEND;
	else if (tok->string[0] == '"' && tok->string[ft_strlen(tok->string)
		- 1] == '"')
		tok->type = D_QUOTE;
	else if (tok->string[0] == '\'' && tok->string[ft_strlen(tok->string)
		- 1] == '\'')
		tok->type = S_QUOTE;
	else if (ft_strlen(tok->string) != 0)
		tok->type = ARG;
}

int	decide_token_type(t_cmd **line)
{
	t_cmd	*curr;
	t_token	*tok;

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

int	initialize_tokens(char *arg, t_token **type)
{
	t_token	*new;

	new = NULL;
	new = new_token(arg, new);
	//	printf("		Arg for token is %s\n", arg);
	if (new == NULL)
	{
		free(arg);
		return (30);
	}
	
	token_add_back(type, new);
	free(arg);
	return (0);
}

void	token_add_back(t_token **begin, t_token *new)
{
	t_token	*token;

	token = *begin;
	if (begin)
	{
		if (*begin == NULL)
			*begin = new;
		else
		{
			token = token_last((*begin));
			token->next = new;
		}
		new = NULL;
	}
}

t_token	*token_last(t_token *lst)
{
	t_token	*current;

	current = lst;
	if (lst == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}
