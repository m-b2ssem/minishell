
#include "../minishell.h"

char	*create_expansion(t_env *curr, char *org, int start, char *tmp)
{
	int		new_size;
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	j = 0;
	expanded = NULL;
	new_size = calculate_size(curr, org, tmp);
	if (new_size == 0)
		return (NULL);
	expanded = malloc(sizeof(char) * (new_size + 1));
	if (!expanded)
		return (NULL);
	while (i < (start - 1))
		expanded[j++] = org[i++];
	i = 0;
	while (curr->value[i])
		expanded[j++] = curr->value[i++];
	start += ft_strlen(tmp);
	while (org[start])
		expanded[j++] = org[start++];
	expanded[j] = '\0';
	if (!expanded || expanded[0] == '\0')
		return (NULL);
	return (expanded);
}

char	*forbidden_variable_name(t_token *tok, char *tmp, int start)
{
	char	*expand;
	char	*org;
	int		new_size;
	int		i;
	int		j;
	int		new_start;

	j = 0;
	org = tok->string;
	i = 0;
	expand = NULL;
	new_size = 0;
	new_size = ft_strlen(tok->string) - ft_strlen(tmp);
	expand = malloc(sizeof(char) * new_size);
	if (!expand)
		return (NULL);
	while (i < (start - 1))
	{
		expand[i] = org[i];
		i++;
	}
	j = i;
	new_start = start + ft_strlen(tmp);
	while (org[new_start])
	{
		expand[j] = org[new_start];
		new_start++;
		j++;
	}
	expand[j] = '\0';
	return (expand);
}

char	*get_env_value(char *tmp_name, t_token *tok, t_env **list, int start)
{
	t_env	*curr;
	char	*org_str;

	org_str = tok->string;
	curr = NULL;
	if (tmp_name == NULL)
		return (NULL);
	curr = find_accord_env_name(tmp_name, list);
	if (curr == NULL)
		return (forbidden_variable_name(tok, tmp_name, start));
	return (create_expansion(curr, org_str, start, tmp_name));
}

void	possible_expansion(t_cmd **cmd, t_token *tok, int status)
{
	int		i;
	int		start_name;
	int		size;
	char	*tmp_name;
	char	*expand;

	expand = NULL;
	size = 0;
	tmp_name = NULL;
	i = 0;
	start_name = 0;
	size = ft_strlen(tok->string);
	if (size == 0)
		return ;
	if (!tok || !tok->string)
		return ;
	while (i < size)
	{
		while (tok->string[i] && tok->string[i] != '$')
			i++;
		if (tok->string[i] != '$')
			return ;
		while (tok->string[i] == '$')
			i++;
		start_name = i;
		if (!is_valid_char_begin(tok->string[start_name + 1]))
			return ;
		while (tok->string[i] && tok->string[i] != '$'
			&& is_valid_char_rest(tok->string[i]))
			i++;
		if (i == start_name)
			continue ;
		tmp_name = ft_substr(tok->string, start_name, i - start_name);
		if (tmp_name)
		{
			expand = get_env_value(tmp_name, tok, &(*cmd)->env, start_name);
			if (expand)
			{
				free(tok->string);
				tok->string = expand;
			}
			if (ft_strcmp(tmp_name, "?") == 0)
			{
				free(tok->string);
				tok->string = ft_strdup(ft_itoa(status));
			}
			free(tmp_name);
		}
	}
}

int	handle_expansion(t_cmd **line, int status)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	int		here;

	here = 0;
	curr_cmd = NULL;
	curr_tok = NULL;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->type == HERE_DOC)
				here = 1;
			else if (curr_tok->string != NULL && curr_tok->string[0] != '\0'
				&& here != 1)
			{
				if ((curr_tok->type == D_QUOTE || curr_tok->type == ARG)
					&& curr_tok->expansion != 1)
					if (ft_strchr(curr_tok->string, '$') != NULL)
						possible_expansion(line, curr_tok, status);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
