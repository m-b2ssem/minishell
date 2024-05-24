#include "../minishell.h"

int	is_valid_char_begin(char c)
{
	if (ft_isalpha(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

int	is_valid_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	return (0);
}

int	is_valid_char_rest(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (1);
	return (0);
}

t_env	*find_accord_env_name(char *tmp, t_env **list)
{
	t_env	*curr;

	curr = *list;
	while (curr != NULL)
	{
		if (ft_strcmp(tmp, curr->name) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

int	calculate_size(t_env *curr, char *org, char *tmp)
{
	int	res;
	int	diff;

	diff = 0;
	res = 0;
	if (!curr || !org || !tmp)
		return (res);
	if (ft_strlen(curr->value) >= ft_strlen(tmp))
		diff = ft_strlen(curr->value) - ft_strlen(tmp);
	else
		diff = ft_strlen(tmp) - ft_strlen(curr->value);
	res = ft_strlen(org) + diff;
	return (res);
}
