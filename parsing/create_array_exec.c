
#include "../minishell.h"

void	initialize_arg_array(t_cmd *cmd)
{
	t_token	*tok;
	int		option;
	int		i;
	int		flag;

	flag = 0;
	option = 0;
	tok = cmd->token;
	i = 0;
	while (tok != NULL)
	{
		while (tok != NULL && tok->type == BLANK)
			tok = tok->next;
		while (tok != NULL)
		{
			if (tok->type == BUILTIN || tok->type == ARG || tok->type == D_QUOTE
				|| tok->type == S_QUOTE)
			{
				cmd->arg_arr[i++] = tok->string;
				option = 0;
			}
			else if (tok->type == OPTION && !option)
			{
				option = 1;
				cmd->arg_arr[i++] = tok->string;
			}
			tok = tok->next;
		}
	}
	cmd->arg_arr[i] = NULL;
}

int	count_arg(t_cmd *cmd)
{
	t_token	*tok;
	int		size;

	size = 0;
	tok = cmd->token;
	while (tok != NULL)
	{
		if (tok->type == ARG || tok->type == BUILTIN || tok->type == D_QUOTE
			|| tok->type == S_QUOTE || tok->type == OPTION)
			size++;
		tok = tok->next;  
	}
	return (size);
}

int	create_arr_for_exec(t_cmd **line)
{
	t_cmd	*curr_cmd;
	char	**arg_arr;
	int		size;

	size = 0;
	curr_cmd = NULL;
	arg_arr = NULL;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		size = count_arg(curr_cmd);
		arg_arr = malloc(sizeof(char *) * (size + 1));
		if (!arg_arr)
			return (1);
		curr_cmd->arg_arr = arg_arr;
		initialize_arg_array(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
