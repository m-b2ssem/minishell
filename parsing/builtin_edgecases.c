
#include "../minishell.h"

int	builtin_export_checker(char *arr)
{
	int	i;
	int	size;

	size = find_char(arr);
	if (size == 0)
		return (1);
	i = 1;
	if (!is_valid_char_begin(arr[0]))
		return (1);
	while (i < size)
	{
		if (!is_valid_char_rest(arr[i]))
			return (1);
		i++;
	}
	return (0);
}
