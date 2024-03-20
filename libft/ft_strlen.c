#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char	*i;

	i = str;
	while (*str)
		str++;
	return (str - i);
}

/*#include <stdio.h>
int main()
{
	char s = "hello word";
	int b = ft_strlen(s);
	printf("the length is %d", b);
}*/