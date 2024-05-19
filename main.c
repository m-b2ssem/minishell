
#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	char *str;
	int		status;
	t_cmd *cmd = NULL;
	t_env *envp = NULL;

	if (!argc && !argv)
		return (0);
	status = 0;
	envp = initialize_env_variables(&envp, env);
	if (envp == NULL)
		return (0);
	while (1)
	{
		// str = readline(PROMPT);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		if (isatty(fileno(stdin)))
			str = readline(PROMPT);
		else
		{
			char *line;
			line = get_next_line(fileno(stdin));
			str = ft_strtrim(line, "\n");
			if (!str)
				break ;
			free(line);
		}
		if (str != NULL && *str != '\0')
			add_history(str);
		if (str == NULL)
		{
			free_list(&envp);
			return (0);
		}
		if (parse_cmd(str, &cmd, envp, status) == 1)
		{
			status = 1;
			free_list(&envp);
			free_everything(&cmd);
		}
		status = execute(&cmd);
		free_everything(&cmd);
		free(str);
	}
	return (0);
}
