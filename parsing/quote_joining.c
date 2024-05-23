
#include "../minishell.h"


char	*join_strings(t_token **head)
{
	char *new;
	int total_len;
	t_token *curr_tok;
	t_token *prev_tok;

	total_len = 0;
	curr_tok = *head;
	while (curr_tok != NULL)
	{
		if (curr_tok->join == 1)
			total_len += (ft_strlen(curr_tok->string)) + 1;
		else if (curr_tok->join == 0 && curr_tok->type == BLANK
			&& prev_tok->join == 1 && prev_tok != NULL)
			break ;
		prev_tok = curr_tok;
		curr_tok = curr_tok->next;
	}
	if (total_len == 0)
		return (NULL);
	new = malloc(sizeof(char) * (total_len + 1));
	if (!new)
		return (NULL);
	new[0] = '\0';
	prev_tok = NULL;
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
		else if (prev_tok != NULL && prev_tok->join == 1
			&& curr_tok->join == 0)
			break ;
		prev_tok = curr_tok;
		curr_tok = curr_tok->next;
	}
	return (new);
}

int	assign_join_variable(t_cmd **cmd)
{
	t_cmd *curr_cmd;
	t_token *curr_tok;
	t_token *prev_tok;
	t_token *head_tok;
	int flag;

	flag = 0;
	curr_cmd = NULL;
	curr_tok = NULL;
	curr_cmd = *cmd;
	head_tok = curr_cmd->token;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		prev_tok = NULL;
		while (curr_tok != NULL)
		{
			if (prev_tok != NULL && !join_redir_helper(prev_tok)
				&& curr_tok->string != NULL && join_quoted_helper(curr_tok))
			{
				if (join_quoted_helper(prev_tok) || (prev_tok->type == BUILTIN
						&& prev_tok != head_tok))
					prev_tok->join = 1;
				curr_tok->join = 1;
				flag++;
			}
			prev_tok = curr_tok;
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (flag);
}

int	find_node_and_modify(char *join, t_token **tok, t_token *find)
{
	t_token *curr_tok;
	t_token *tmp_find;

	curr_tok = *tok;
	tmp_find = find;

	while (curr_tok != NULL)
	{
		if (curr_tok == tmp_find)
		{
			if (curr_tok->next != NULL)
			{
				if (join == NULL)
					return (1);
				if (join != curr_tok->string)
				{
					free(curr_tok->string);
					curr_tok->string = join;
					curr_tok->join = 0;
					curr_tok->type = ARG;
				}
				if (curr_tok->string == NULL)
					return (1);
			}
		}
		curr_tok = curr_tok->next;
	}
	return (0);
}

int	join_quoted_strings(t_cmd **head)
{
	char *new;
	t_token *first;
	t_cmd *curr_cmd;
	t_token *curr_tok;

	new = NULL;
	first = NULL;
	curr_cmd = *head;
	curr_tok = NULL;
	if (assign_join_variable(head) > 0)
	{
		while (curr_cmd != NULL)
		{
			curr_tok = curr_cmd->token;
			while (curr_tok != NULL)
			{
				while (curr_tok != NULL && curr_tok->join != 1)
					curr_tok = curr_tok->next;
				if (curr_tok == NULL)
				{
					if (curr_cmd->next != NULL)
					{
						curr_cmd = curr_cmd->next;
						continue ;
					}
					else
						break ;
				}
				first = curr_tok;
				new = join_strings(&curr_tok);
				if (new)
				{
					find_node_and_modify(new, &curr_tok, first);
					find_and_modify_unused_nodes(first);
				}
				curr_tok = first->next;
			}
			curr_cmd = curr_cmd->next;
		}
	}
	return (0);
}
