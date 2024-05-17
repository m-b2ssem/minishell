
#include "../minishell.h"

void	initialize_arg_array(t_cmd *cmd)
{
	t_token	*tok;
	int		i;
	int		flag;
	int		first_arg_found;

	tok = cmd->token;
	i = 0;
	flag = 0;
	first_arg_found = 0;
	while (tok != NULL)
	{
		while (tok != NULL && tok->type == BLANK)
			tok = tok->next;
		while (tok != NULL)
		{
			if (tok->type == ARG || tok->type == BUILTIN || tok->type == D_QUOTE
				|| tok->type == S_QUOTE || tok->type == OPTION)
			{
				if (i == 0 || tok->type == OPTION)
					first_arg_found = 1;
				else
					first_arg_found = 0;
				cmd->arg_arr[i++] = tok->string;
				flag = 0;
			}
			else if (tok->type == BLANK)
			{
				if (!flag && !first_arg_found)
				{
					cmd->arg_arr[i++] = tok->string;
					flag = 1;
				}
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
			|| tok->type == S_QUOTE || tok->type == BLANK)
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
