#include "../minishell.h"

int	parse_cmd(char *str, t_cmd **line, t_env *env, int status)
{
	char	**arr;

	if (first_string_checks(str) == 1)
		return (1);
	arr = ft_split_cmd(str, '|');
	if (arr == NULL || arr[0] == NULL)
		return (1);
	initialize_arguments(line, arr, env);
	iterate_through_cmd_args(line);
	decide_token_type(line);
	if (redirection_spell_check(line) == 1)
	{
		ft_putstr_fd(REDIR, 2);
		return (1);
	}
	search_quotes_modify(line);
	handle_expansion(line, status);
	remove_lone_dollars(line);
	join_quoted_strings(line);
	redirection_usage(line);
	echo_option_checker(line);
	remove_blank_tokens_from_cmds(line);
	create_arr_for_exec(line);
	return (0);
}

void	handle_expansion_edgecase(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	t_token	*prev;
	int		here;

	here = 0;
	curr_cmd = *line;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		prev = NULL;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->type == HERE_DOC)
				here = 1;
			else if (here && curr_tok->string != NULL
				&& (curr_tok->type == S_QUOTE || curr_tok->type == D_QUOTE)
				&& prev != NULL && prev->type == ARG)
				prev->type = curr_tok->type;
			prev = curr_tok;
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
}
