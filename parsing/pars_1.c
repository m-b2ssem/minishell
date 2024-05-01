
#include "../libft/libft.h"
#include "../minishell.h"
#include <string.h>

t_quote_status	get_quote_status(char c, t_quote_status stat);

t_cmd add_argument_to_list(char *arg, int i, t_cmd *line)
{

}

int	is_pipe(char c)
{
	return (c == '|');
}

int	save_input_in_struct(char *str, t_cmd **line)
{
	int				i;
	int				start;
	char			*arg;
	t_quote_status	stat;

	i = 0;
	start = 0;
	stat = NO_QUOTE;
	get_quote_status(str[i], stat);
	while (str[i])
	{
		if (is_pipe(str[i]) && stat == NO_QUOTE)
		{
			arg = ft_substr(str, start, i - 1 - start);
			printf("---------------ARG %s\n", arg);
			start = i + 1;
			free(arg);
		}
		get_quote_status(str[i], stat);
		i++;
	}
	if (start < i && stat == NO_QUOTE)
	{
		arg = ft_substr(str, start, i - start);
		printf("---------------ARG %s\n", arg);
		free(arg);
	}
	return (0);
}

t_quote_status	get_quote_status(char c, t_quote_status stat)
{
	if (c == '\'' && stat != SINGLE)
		stat = SINGLE;
	else if (c == '"' && stat != DOUBLE)
		stat = DOUBLE;
	else if ((c == '\'' && stat == SINGLE) || (c == '"' && stat == DOUBLE))
		stat = NO_QUOTE;
	return (stat);
}

int	parsing_entry(char *user_input)
{
	t_quote_status	status;
	int				i;
	char			current_char;

	if (user_input == NULL)
	{
		return (0);
	}
	status = NO_QUOTE;
	i = 0;
	while (user_input[i])
	{
		status = get_quote_status(user_input[i], status);
		i++;
	}
	return (status != NO_QUOTE); // Return 1 for unclosed quotes, 0 otherwise
}

int	main(int argc, char **argv)
{
	int	quote;

	(void)argc;
	if (argc == 2)
	{
		save_input_in_struct(argv[1], NULL);
		if ((quote = parsing_entry(argv[1])) == 0)
		{
			printf("s1: No unclosed quotes\n");
		}
		else
		{
			printf("s1: Unclosed quotes detected\n");
		}
	}
	else
		printf("No arguments\n");
	return (0);
}
