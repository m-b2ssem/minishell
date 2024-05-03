
#include "minishell.h"

int	main(int argc, char *argv[])
{
	t_cmd	*line;
	char	*str;
	int		i;

	line = NULL;
	i = 0;
	// memset(line, 0, sizeof(t_cmd));
	if (argc > 1)
	{
		str = argv[1];
		i = check_for_unclosed_quotes(str);
		if (i != 0)
			printf("Unclosed detected\n");
		else
		{
			lexer(argv[1], &line);
			// print_list(line);
			free_list(&line);
		}
	}
	else
	{
		printf("minishell: missing arguments\n");
		// Inform about missing arguments
	}
	return (0);
}
