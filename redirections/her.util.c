#include "../minishell.h"

char	*get_after_dollar(t_dollar_vars *vars, char **after_doller, int *k)
{
	(*vars->i)++;
	*after_doller = malloc(sizeof(char) * (strlen(vars->str) + 1));
	if (!*after_doller)
		return (free(vars->new_str), NULL);
	while (vars->str[*vars->i] != '\0' && vars->str[*vars->i] != ' ')
		(*after_doller)[(*k)++] = vars->str[(*vars->i)++];
	(*after_doller)[*k] = '\0';
	return (*after_doller);
}

char	*process_dollar(t_dollar_vars *vars)
{
	char	*after_doller;
	char	*var_value;
	int		k;

	k = 0;
	after_doller = get_after_dollar(vars, &after_doller, &k);
	if (!after_doller)
		return (NULL);
	var_value = my_getenv(after_doller, vars->env);
	if (var_value && vars->tok->expansion == 0)
	{
		strcpy(&vars->new_str[*vars->j], var_value);
		*vars->j += strlen(var_value);
	}
	else
	{
		vars->new_str[(*vars->j)++] = '$';
		strcpy(&vars->new_str[*vars->j], after_doller);
		*vars->j += k;
	}
	free(after_doller);
	return (vars->new_str);
}

char	*handle_doller(t_dollar_vars *vars)
{
	vars->new_str = process_dollar(vars);
	if (!vars->new_str)
		return (NULL);
	return (vars->new_str);
}

char	*my_getenv(char *name, t_env *env)
{
	t_env	*tmp;
	int		len;

	tmp = env;
	len = ft_strlen(name);
	while (tmp->next != NULL)
	{
		if (ft_strncmp(tmp->name, name, len) == 0 && tmp->export == 1)
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}