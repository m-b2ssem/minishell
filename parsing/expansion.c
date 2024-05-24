#include "../minishell.h"

extern int	g_signal;

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
			}
			curr_token = curr_token->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

void	generate_args_for_tok(t_token *tok, t_token **last_new,
		t_token **new_list)
{
	char	*new;
	int		size;
	int		i;
	int		start;

	initialize_generate_args_variables(&i, &start, &new);
	size = ft_strlen(tok->string);
	while (i < size)
	{
		start = i;
		if (is_redirection(tok->string[i]))
			get_redirection(tok->string, &i);
		else if (is_space(tok->string[i]))
			i++;
		else
			get_arguments(tok->string, &i);
		new = ft_substr(tok->string, start, i - start);
		if (reinit(new, new_list, last_new) == 1)
		{
			free(new);
			break ;
		}
	}
	free(tok->string);
	free(tok);
}
