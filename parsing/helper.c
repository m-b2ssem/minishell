
#include "../minishell.h"

void	update_eof_expansion(t_token *tok)
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

char	*create_expansion(t_env *curr, char *org, int start, char *tmp)
{
	int		diff;
	int		new_size;
	char	*expanded;
	int		i;
	int		j;
	char	*tmp_value;

	i = 0;
	j = 0;
	diff = 0;
	new_size = 0;
	expanded = NULL;
	if (ft_strlen(curr->value) > ft_strlen(tmp))
		diff = ft_strlen(curr->value) - ft_strlen(tmp);
	else
		diff = ft_strlen(tmp) - ft_strlen(curr->value);
	new_size = ft_strlen(org) + diff;
	expanded = malloc(sizeof(char) * (new_size + 1));
	if (!expanded)
		return (NULL);
	tmp_value = NULL;
	tmp_value = ft_strdup(curr->value);
	if (expanded)
	{
		while (i <= start)
		{
			expanded[i] = org[j];
			j++;
			i++;
		}
		start = j;
		j = 0;
		while ((size_t)i <= ft_strlen(curr->value))
		{
			expanded[i] = tmp_value[j];
			j++;
			i++;
		}
		while ((size_t)start <= ft_strlen(org))
		{
			expanded[i] = org[start];
			start++;
			i++;
		}
	}
	else
		return (NULL);
	return (expanded);
}

char	*get_env_value(char *new, char *org, t_env **list, int *i)
{
	t_env	*curr;
	char	*tmp;
	int		start;

	curr = NULL;
	(void)list;
	start = 0;
	while (org[*i] != '\0' && org[*i] == '$')
		(*i)++;
	start = *i + 1;
	while (org[*i] != '\0' && org[*i] != ' ' && org[*i] != '$')
		(*i)++;
	tmp = ft_substr(org, start, *i - start);
	if (tmp == NULL)
		return (NULL);
	while (curr != NULL)
	{
		if (ft_strcmp(tmp, curr->name) == 0)
		{
			new = create_expansion(curr, org, start - 1, tmp);
			if (new == NULL)
				printf("WHAT DID YOU DO??\n");
		}
		curr = curr->next;
	}
	return (new);
}

char	*double_quote_expansion(t_token *tok, char *str, char *new)
{
	int		i;
	char	s1[] = "\"";
	t_env	**list;

	list = NULL;
	(void)tok;
	if (str == NULL)
		return (NULL);
	i = 0;
	if (str[i] == '"')
		i++;
	while (str && str[i] != '\0' && str[i] != '"')
	{
		if (str[i] == '$')
		{
			new = get_env_value(new, str, list, &i);
		}
		else
		{
			new = ft_strtrim(str, s1);
		}
		i++;
	}
	return (new);
}

int	update_string_expansion(t_token *tok)
{
	char	s2[] = "\'";
	char	*expand;

	expand = NULL;
	if (tok->type == S_QUOTE)
	{
		expand = ft_strtrim(tok->string, s2);
		if (expand == NULL)
			return (-1);
		if (expand != tok->string)
		{
			free(tok->string);
			tok->string = ft_strdup(expand);
			free(expand);
		}
		if (!tok->string)
			return (-1);
	}
	else if (tok->type == D_QUOTE)
	{
		expand = double_quote_expansion(tok, tok->string, expand);
	}
	return (0);
}

int	the_expander(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	char	*new;

	new = NULL;
	(void)new;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string && curr_tok->string[0]
				&& curr_tok->expansion == 1)
			{
				if (curr_tok->type == D_QUOTE || curr_tok->type == S_QUOTE)
					update_eof_expansion(curr_tok);
				// if (curr_tok->type == DELIM)
				// 	update_eof_expansion(curr_tok);
				// else if (curr_tok->type == D_QUOTE
				//|| curr_tok->type == S_QUOTE)
				// 	update_string_expansion(curr_tok);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
