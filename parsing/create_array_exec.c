
#include "../minishell.h"

void	initialize_arg_array(t_cmd *cmd)
{
	t_token	*tok;
	int		i;

	tok = NULL;
	i = 0;
	tok = cmd->token;
	while (tok != NULL)
	{
		if (tok->type == ARG || tok->type == BUILTIN || tok->type == D_QUOTE
			|| tok->type == S_QUOTE)
		{
			cmd->arg_arr[i] = tok->string;
			i++;
		}
		tok = tok->next;
	}
	cmd->arg_arr[i] = NULL;
}

int	count_arg(t_token **token)
{
	int		size;
	t_token	*tok;

	tok = *token;
	size = 0;
	while (tok != NULL)
	{
		if (tok->type == ARG || tok->type == BUILTIN || tok->type == D_QUOTE
			|| tok->type == S_QUOTE)
			size++;
		tok = tok->next;
	}
	return (size);
}

int	create_arr_for_exec(t_cmd **line)
{
	t_cmd	*curr_cmd;
	char	**arg_arr;
	int		d;

	curr_cmd = NULL;
	arg_arr = NULL;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		// size = cmd_lenth(curr_cmd);
		d = count_arg(&curr_cmd->token);
		// printf("SIZEIST :__________%d\n", d);
		arg_arr = malloc(sizeof(char *) * (d + 1));
		if (!arg_arr)
			return (1);
		curr_cmd->arg_arr = arg_arr;
		initialize_arg_array(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
