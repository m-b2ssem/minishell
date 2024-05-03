#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	cur;
	char	*data_dst;
	char	*data_src;

	cur = 0;
	data_dst = (char *)dst;
	data_src = (char *)src;
	if (!src && !dst)
		return (NULL);
	while (cur < n)
	{
		data_dst[cur] = data_src[cur];
		cur++;
	}
	return (data_dst);
}

/*
#include <stdio.h>
#include <string.h>

int main () {
   const char src[50] = "Hello Word";
   char dest[50] = "hello";
   
   printf("Before ft_memcpy dest = %s\n", dest);
   ft_memcpy(dest, src, strlen(src)+1);
   printf("After ft_memcpy dest = %s\n", dest);
   
   return(0);
}*/
