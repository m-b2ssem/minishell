#include "../minishell.h"

extern int	g_signal;

t_token	*reinitialize_tokens(char *s)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->string = s;
	new->type = NON;
	token_type(new);
	new->expansion = -1;
	new->next = NULL;
	return (new);
}

int	reinit(char *s, t_token **new_list, t_token **last_new)
{
	t_token	*new;

	new = reinitialize_tokens(s);
	if (!new)
		return (1);
	if (!*new_list)
		*new_list = new;
	else
		(*last_new)->next = new;
	*last_new = new;
	return (0);
}

void	init_args_var(int *i, int *start, char **new)
{
	*i = 0;
	*start = 0;
	*new = NULL;
}

char	*forbidden_variable_name(t_token *tok, char *tmp, int start)
{
	char	*expand;
	int		new_size;
	int		i;
	int		j;
	int		new_start;

	i = 0;
	j = 0;
	expand = NULL;
	new_size = ft_strlen(tok->string) - ft_strlen(tmp);
	expand = malloc(sizeof(char) * new_size);
	if (!expand)
		return (NULL);
	while (i < (start - 1))
	{
		expand[i] = tok->string[i];
		i++;
	}
	j = i;
	new_start = start + ft_strlen(tmp);
	while (tok->string[new_start])
		expand[j++] = tok->string[new_start++];
	expand[j] = '\0';
	return (expand);
}

void	hand_exp_loop(t_cmd **line, t_token *curr_tok, int status)
{
	int	here;

	here = 0;
	while (curr_tok != NULL)
	{
		if (curr_tok->type == HERE_DOC)
			here = 1;
		else if (curr_tok->string != NULL && curr_tok->string[0] != '\0'
			&& here != 1)
		{
			if ((curr_tok->type == D_QUOTE || curr_tok->type == ARG)
				&& curr_tok->expansion != 1)
			{
				if (ft_strchr(curr_tok->string, '$') != NULL)
				{
					possible_expansion(line, curr_tok, status);
					retokenizing_of_env_values(line, curr_tok);
				}
			}
		}
		curr_tok = curr_tok->next;
	}
}
