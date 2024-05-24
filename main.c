#include "minishell.h"

extern int	g_signal;

int	is_all_whitespace(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (!is_space((char)*str))
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	int	status;
	t_cmd	*cmd;
	t_env	*envp;

	cmd = NULL;
	envp = NULL;
	if (!argc && !argv)
		return (0);
	status = 0;
	envp = initialize_env_variables(&envp, env);
	if (envp == NULL)
		return (0);
	parent_signals();
	while (1)
	{
		str = readline(PROMPT);
		if (str == NULL)
		{
			free_list(&envp);
			return (0);
		}
		if (is_all_whitespace(str))
			continue ;
		if (str != NULL && *str != '\0')
			add_history(str);
		if (parse_cmd(str, &cmd, envp, status) == 1)
		{
			status = 1;
			free_everything(&cmd);
		}
		else
		{
			status = execute(&cmd);
			free_everything(&cmd);
		}
		free(str);
	}
	return (0);
}
