#include "../minishell.h"

char	*my_strcat(char *destination, const char *source)
{
	char	*temp;

	temp = destination;
	while (*destination)
		destination++;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return (temp);
}

int	strcmp_custom(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

char	*strcpy_custom(char *destination, const char *source)
{
	char	*temp;

	temp = destination;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return (temp);
}
