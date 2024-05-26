#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*s;
	char		*d;
	size_t		i;

	if (dst == 0 && src == 0)
		return (dst);
	s = (char *)src;
	d = (char *)dst;
	i = 0;
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
