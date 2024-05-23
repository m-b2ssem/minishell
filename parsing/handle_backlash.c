
#include "../minishell.h"

t_slash_status	get_backslash_status(char c, t_slash_status stat)
{
	if (c == '\\' && stat == NO_SLASH)
		stat = OPEN;
	else if (c == '\\' && stat == OPEN)
		stat = NO_SLASH;
	return (stat);
}

void	modify_string_backslash(t_token *tok, char *str)
{
	int				i;
	int				start;
	int				end;
	int				slash_nbr;
	t_slash_status	stat;
	int				j;
	int				new_length;
	char			*new_str;

	end = 0;
	slash_nbr = 0;
	start = 0;
	stat = NO_SLASH;
	i = 0;
	while (str[i] != '\0' && str[i] != '\\')
		i++;
	start = i;
	while (str[i] != '\0' && str[i] == '\\')
	{
		stat = get_backslash_status(str[i], stat);
		i++;
	}
	end = i;
	if (stat == OPEN)
	{
		slash_nbr = ((i - start) / 2) + 1;
		tok->expansion = 1;
	}
	else
	{
		slash_nbr = (i - start) / 2;
		tok->expansion = 0;
	}
	new_length = slash_nbr + ft_strlen(str) - end;
	new_str = malloc(sizeof(char) * (new_length + 1));
	if (!new_str)
		return ;
	i = 0;
	while (i < slash_nbr)
		new_str[i++] = '\\';
	j = 0;
	while (str[end + j])
		new_str[i++] = str[end + j++];
	new_str[i] = '\0';
	free(tok->string);
	tok->string = new_str;
}

int	handle_backslash(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;

	curr_cmd = NULL;
	curr_tok = NULL;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->string[0] != '\0')
			{
				if ((curr_tok->type == ARG || curr_tok->type == D_QUOTE)
					&& ft_strchr(curr_tok->string, '\\') != NULL)
					modify_string_backslash(curr_tok, curr_tok->string);
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
