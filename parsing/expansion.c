
#include "../minishell.h"

int	calculate_size(t_env *curr, char *org, char *tmp)
{
	int	res;
	int	diff;

	diff = 0;
	res = 0;
	if (!curr || !org || !tmp)
		return (res);
	if (ft_strlen(curr->value) >= ft_strlen(tmp))
		diff = ft_strlen(curr->value) - ft_strlen(tmp);
	else
		diff = ft_strlen(tmp) - ft_strlen(curr->value);
	res = ft_strlen(org) + diff;
	return (res);
}

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
	// free the memory here
	return (expanded);
}

char	*get_env_value(char *tmp_name, char *org_str, t_env **list, int start)
{
	t_env	*curr;

	curr = NULL;
	if (tmp_name == NULL)
		return (NULL);
	curr = find_accord_env_name(tmp_name, list);
	if (curr == NULL)
		return (NULL);
	return (create_expansion(curr, org_str, start, tmp_name));
}

void	possible_expansion(t_cmd **cmd, t_token *tok)
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
			expand = get_env_value(tmp_name, tok->string, &(*cmd)->env,
					start_name);
			free(tmp_name);
			if (expand)
			{
				free(tok->string);
				tok->string = expand;

			}

		}
	}
}

int	handle_expansion(t_cmd **line)
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
				if (curr_tok->type == D_QUOTE || curr_tok->type == ARG)
					if (ft_strchr(curr_tok->string, '$') != NULL)
						possible_expansion(line, curr_tok);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
