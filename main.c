
#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	char *str;
	t_cmd *cmd = NULL;
	t_env *envp = NULL;

	if (!argc && !argv)
		return (0);
	envp = initialize_env_variables(&envp, env);
	if (envp == NULL)
		return (0);
	while (1)
	{
		str = readline(PROMPT);
		if (str != NULL && *str != '\0')
			add_history(str);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		// if (isatty(fileno(stdin)))
		// 	str = readline(PROMPT);
		// else
		// {
		// 	char *line;
		// 	line = get_next_line(fileno(stdin));
		// 	str = ft_strtrim(line, "\n");
		// 	if (!str)
		// 		break ;
		// 	free(line);
		// }
		if (str == NULL)
		{
			free_list(&envp);
			return (0);
		}

		if (parse_cmd(str, &cmd, envp) == 1)
		{
			free_list(&envp);
			free_everything(&cmd);
		}
		execute(&cmd);
		free_everything(&cmd);
		free(str);
	}
	free_list(&envp);
	free_everything(&cmd);
	return (0);
}
