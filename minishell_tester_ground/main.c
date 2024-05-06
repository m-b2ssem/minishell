
#include "minishell.h"

void	free_str(char *str)
{
	if (str)
		free(str);
}

int	main(int argc, char *argv[])
{
	t_cmd	*line;
	char	*user;
	char	**arr;
	int		i;
	int		res;

	line = NULL;
	arr = NULL;
	// line = NULL;
	i = 0;
	if (!argc && !argv)
		return (0);
	while (1)
	{
		user = readline("💅 🧠 minishell> ");
		add_history(user);
		if (user == NULL)
			continue ;
		res = check_for_unclosed_quotes(user);
		if (res != 0)
			printf("Unclosed detected\n");
		else
		{
			arr = ft_split_cmd(user, '|');
			initialize_arguments(&line, arr);
			iterate_through_cmd_args(&line);
			print_list(line);
		}
		// free(arr);
		// // ;
		// if (user != NULL)
		// 	free(user);
		// free_list(line);
	}
	return (0);
}
