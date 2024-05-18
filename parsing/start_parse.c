
#include "../minishell.h"

int	parse_cmd(char *str, t_cmd **line, t_env *env, int status)
{
	char	**arr;
	int		check;

	check = 0;
	(void)check;
	if (first_string_checks(str) == 1)
		return (1);
	// should not go into the split_cmd function
	arr = ft_split_cmd(str, '|');
	if (arr == NULL || arr[0] == NULL || arr[0][0] == '\0')
		return (1);
	initialize_arguments(line, arr, env);
	iterate_through_cmd_args(line);
	decide_token_type(line);
	if (redirection_spell_check(line) == 1)
	{
		ft_putstr_fd(REDIR, 1);
		return (1);
	}
	search_quotes_modify(line);
	handle_backslash(line);
	handle_expansion(line, status);
	join_quoted_strings(line);
	redirection_usage(line);
	echo_option_checker(line);
	create_arr_for_exec(line);
	print_arr(line);
	return (0);
}
