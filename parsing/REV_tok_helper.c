
#include "../minishell.h"

char	*join_strings(t_token **head)
{
	char	*new;
	int		total_len;
	t_token	*curr_tok;

	total_len = 0;
	curr_tok = *head;
	while (curr_tok != NULL)
	{
		if (curr_tok->join == 1)
			total_len += (ft_strlen(curr_tok->string) + 1);
		curr_tok = curr_tok->next;
	}
	if (total_len > 0)
	{
		new = malloc(sizeof(char) * (total_len + 1));
		if (!new)
			return (NULL);
		new[0] = '\0';
	}
	curr_tok = *head;
	while (curr_tok != NULL)
	{
		if (curr_tok->join == 1)
		{
			new = strcat(new, curr_tok->string);
			if (new == NULL)
				return (NULL);
			new = strcat(new, "");
		}
		curr_tok = curr_tok->next;
	}
	return (new);
}

int	join_quoted_helper(t_token *curr_tok)
{
	if (curr_tok->type == D_QUOTE || curr_tok->type == S_QUOTE
		|| curr_tok->type == ARG)
		return (1);
	return (0);
}

int	assign_join_variable(t_cmd **cmd)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	t_token	*prev_tok;
	t_token	*first;
	char	*new;

	new = NULL;
	curr_cmd = *cmd;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		prev_tok = NULL;
		first = NULL;
		while (curr_tok != NULL)
		{
			if (prev_tok != NULL && prev_tok->type != BLANK
				&& curr_tok->string != NULL && curr_tok->string[0] != '\0'
				&& join_quoted_helper(curr_tok))
			{
				if (join_quoted_helper(prev_tok))
				{
					prev_tok->join = 1;
					if (first == NULL)
						first = prev_tok;
				}
				curr_tok->join = 1;
			}
			prev_tok = curr_tok;
			curr_tok = curr_tok->next;
		}
		new = join_strings(&curr_cmd->token);
		if (new == NULL)
			return (1);
		if (find_node_and_modify(new, &curr_cmd->token, first) == 1)
			return (1);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}

int	join_quoted_strings(t_cmd **cmd)
{
	if (assign_join_variable(cmd) == 1)
		return (1);
	return (0);
}

int	find_node_and_modify(char *join, t_token **tok, t_token *find)
{
	t_token	*curr_tok;

	curr_tok = *tok;
	while (curr_tok != NULL)
	{
		if (curr_tok == find)
		{
			if (curr_tok->next->string[0] != '\0' && curr_tok->next != NULL)
			{
				if (join == NULL)
					return (1);
				if (join != curr_tok->string)
				{
					free(curr_tok->string);
					curr_tok->string = ft_strdup(join);
					curr_tok->join = 0;
					curr_tok->type = ARG;
					free(join);
				}
				if (curr_tok->string == NULL)
					return (1);
			}
		}
		curr_tok = curr_tok->next;
	}
	return (find_and_modify_unused_nodes(find));
}

int	find_and_modify_unused_nodes(t_token *tok)
{
	if (tok == NULL)
		return (1);
	if (tok->next != NULL && join_quoted_helper(tok))
	{
		tok = tok->next;
		while (tok != NULL)
		{
			if (tok->type != BLANK && tok->join == 1)
			{
				tok->type = NON;
				tok->join = 0;
			}
			tok = tok->next;
		}
	}
	return (0);
}
