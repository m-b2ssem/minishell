#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	cur;
	char	*data;

	cur = 0;
	data = b;
	while (cur < len)
	{
		data[cur] = c;
		cur++;
	}
	return (b);
}

/* #include <stdio.h>

int main() {
    // Define an array of characters
    char str[] = "Hello, World!";

    // Display the original string
    printf("Original String: %s\n", str);

    // Use ft_memset to fill the string with 'X' from index 6 to 11
    ft_memset(str + 6, 'X', 5);

    // Display the modified string
    printf("Modified String: %s\n", str);

    return 0;
}*/