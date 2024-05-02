
#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_cmd	*line;

	(void)line;
	if (argc > 1)
	{
		lexer(argv[1], NULL);
	}
	else
	{
		printf("minishell: missing arguments\n");
			// Inform about missing arguments
	}
	return (0);
}
