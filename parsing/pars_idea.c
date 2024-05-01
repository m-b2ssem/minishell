
#include "../libft/libft.h"
#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
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

t_cmd	*init_arg_list(t_cmd **line, t_cmd *new)
{
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	memset(new, 0, sizeof(t_cmd));
}

t_cmd	*argument_into_list(t_cmd **line, char *arg)
{
	t_cmd	*new;

	init_arg_list(&line, new);
	new->args = malloc(sizeof(char) * strlen(arg));
	if (!new->args)
		return (NULL);
	new->args = strcpy(new->args, arg);
	printf("%s\n", new->args);
}

int	lexer(char *user_input, t_cmd **line)
{
	int				i;
	int				start;
	char			*arg;
	t_quote_status	quote;

	quote = NO_QUOTE;
	i = 0;
	start = 0;
	arg = NULL;
	while (user_input && user_input[i])
	{
		while (is_space(user_input[i]) && user_input[i] != '\0')
			i++;
		quote = get_quote_status(user_input[i], quote);
		if (user_input[i] == '|' && quote == NO_QUOTE)
		{
			arg = ft_substr(arg, start, i - start);
			argument_into_list(&line, arg);
			start = i;
			free(arg);
		}
		i++;
	}
	if (start < i && quote == NO_QUOTE)
	{
		arg = ft_substr(user_input, start, i - start);
		argument_into_list(&line, arg);
		free(arg);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_cmd	*line;

	if (argc > 2)
	{
		lexer(argv[1], &line);
	}
	else
		printf("NO");
	return (0);
}
