#include "../minishell.h"

int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("minishell");
		return (1);
	}
	if (pwd)
	{
		printf("%s\n", pwd);
	}
	else
	{
		return (1);
	}
	free(pwd);
	return (0);
}
