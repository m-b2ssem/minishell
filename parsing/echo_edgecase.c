
#include "../minishell.h"

void	modify_echo_option(t_token *tok)
{
	if (tok == NULL || tok->string == NULL)
		return ;
	free(tok->string);
	tok->string = ft_strdup("-n");
}

int	validate_echo_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (t1[i] != t2[i] || t1[i] == 0 || t2[i] == 0)
			return (t1[i] - t2[i]);
		i++;
	}
	return (0);
}

int	echo_option_checker(t_cmd **line)
{
	t_cmd	*curr_cmd;
	t_token	*curr_tok;
	int		echo;

	echo = 0;
	curr_cmd = *line;
	curr_tok = NULL;
	while (curr_cmd != NULL)
	{
		curr_tok = curr_cmd->token;
		while (curr_tok != NULL)
		{
			if (curr_tok->string != NULL && curr_tok->string[0] != '\0'
				&& echo == 0)
			{
				if (ft_strcmp(curr_tok->string, "echo") == 0)
					echo = 1;
			}
			else if (echo == 1 && join_quoted_helper(curr_tok)
				&& ft_strncmp("-n", curr_tok->string, 2) == 0)
			{
				if (validate_echo_option(curr_tok->string) == 0)
				{
					modify_echo_option(curr_tok);
					curr_tok->type = OPTION;
				}
			}
			curr_tok = curr_tok->next;
		}
		curr_cmd = curr_cmd->next;
	}
	return (0);
}
