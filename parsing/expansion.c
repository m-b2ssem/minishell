
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
		if (!is_valid_char_begin(tok->string[start_name]))
			return ;
		while (tok->string[i] && tok->string[i] != '$'
			&& is_valid_char_rest(tok->string[i]))
			i++;
		if (i == start_name)
			continue ;
		tmp_name = ft_substr(tok->string, start_name, i - start_name);
		if (tmp_name)
		{
			if (ft_strcmp(tmp_name, "?") == 0)
				expand = expand_exit_status(tok, start_name, status);
			else
				expand = get_env_value(tmp_name, tok, &(*cmd)->env, start_name);
			if (expand)
			{
				free(tok->string);
				tok->string = expand;
				size = ft_strlen(tok->string);
				i = 0;
			}
			free(tmp_name);
		}
	}
}

char	*expand_exit_status(t_token *tok, int start, int status)
{
	char	*expand;
	char	*org;
	char	*s;
	int		i;
	int		new_size;
	int		j;
	int		new_start;

	j = 0;
	expand = NULL;
	org = tok->string;
	s = ft_itoa(status);
	i = 0;
	new_size = 0;
	new_start = 0;
	new_size = ft_strlen(tok->string) - 1 + ft_strlen(ft_itoa(status));
	expand = malloc(sizeof(char) * new_size + 1);
	if (!expand)
		return (NULL);
	while (i < (start - 1))
	{
		expand[i] = org[i];
		i++;
	}
	j = i;
	i = 0;
	while (s[i])
	{
		expand[j] = s[i];
		i++;
		j++;
	}
	new_start = start + 1;
	while (org[new_start])
	{
		expand[j] = org[new_start];
		new_start++;
		j++;
	}
	expand[j] = '\0';
	return (expand);
}

int	remove_lone_dollars(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_token;
	int		flag;

	flag = 0;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_token = curr_cmd->token;
		while (curr_token != NULL)
		{
			if (curr_token->string != NULL && ft_strcmp(curr_token->string,
					"exit") == 0)
				flag = 1;
			else if (curr_token->string != NULL)
			{
				if (!flag && ft_strcmp(curr_token->string, "$") == 0
					&& curr_token->type == ARG)
					curr_token->type = BLANK;
				else if (!flag && ft_strlen(curr_token->string) == 0
					&& (curr_token->type == D_QUOTE
						|| curr_token->type == S_QUOTE))
					curr_token->type = BLANK;
			}
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

int	handle_expansion(t_cmd **line, int status)
{
	t_cmd	*curr_cmd;
	int		here;
	t_token	*curr_tok;

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
