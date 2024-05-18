
#include "../minishell.h"

void	initialize_arg_array(t_cmd *cmd)
{
	t_token	*tok;
	int		option;
	int		i;
	int		space;
	int		first_arg_found;

	option = 0;
	tok = cmd->token;
	i = 0;
	space = 0;
	first_arg_found = 0;
	while (tok != NULL)
	{
		while (tok != NULL && tok->type == BLANK)
			tok = tok->next;
		while (tok != NULL)
		{
			if (tok->type == BUILTIN || tok->type == ARG || tok->type == D_QUOTE
				|| tok->type == S_QUOTE)
			{
				if (i == 0)
					first_arg_found = 1;
				else
					first_arg_found = 0;
				cmd->arg_arr[i++] = tok->string;
				space = 0;
				option = 0;
			}
			else if (tok->type == OPTION && !option)
			{
				option = 1;
				cmd->arg_arr[i++] = tok->string;
			}
			else if (tok->type == BLANK && !first_arg_found && !space && !option)
			{
				cmd->arg_arr[i++] = tok->string;
				space = 1;
			}
			tok = tok->next;
		}
	}
	cmd->arg_arr[i] = NULL; // Null-terminate the array
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
			|| tok->type == S_QUOTE || tok->type == BLANK
			|| tok->type == OPTION)
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
		// printf("Size is: %d\n", size);
		arg_arr = malloc(sizeof(char *) * (size + 1));
		if (!arg_arr)
			return (1);
		curr_cmd->arg_arr = arg_arr;
		initialize_arg_array(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
