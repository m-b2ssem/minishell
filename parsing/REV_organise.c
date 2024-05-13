
#include "../minishell.h"

static int	nbr_arg_cmd(t_cmd *cmd)
{
	t_token	*cur_t;
	int		len;

	len = 0;
	cur_t = cmd->token;
	while (cur_t)
	{
		if (cur_t->type == ARG || cur_t->type == BUILTIN)
			len++;
		cur_t = cur_t->next;
	}
	return (len);
}

static void	init_arg(t_cmd *cmd)
{
	t_token	*cur_t;
	int		i;

	cur_t = cmd->token;
	i = 0;
	while (cur_t)
	{
		if (cur_t->type == ARG || cur_t->type == BUILTIN)
		{
			cmd->arg_arr[i] = cur_t->string;
			i++;
		}
		cur_t = cur_t->next;
	}
	cmd->arg_arr[i] = NULL;
}

int	organise_arg(t_cmd **cmd)
{
	t_cmd	*cur_b;
	int				len_arg;
	char			**new;

	cur_b = *cmd;
	while (cur_b)
	{
		len_arg = nbr_arg_cmd(cur_b);
		new = malloc(sizeof(char *) * (len_arg + 1));
		if (new == NULL)
			return (50);
		cur_b->arg_arr = new;
		init_arg(cur_b);
		cur_b = cur_b->next;
	}
	return (0);
}
