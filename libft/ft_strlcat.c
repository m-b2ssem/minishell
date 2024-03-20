#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	cur;

	src_len = ft_strlen(dst);
	cur = 0;
	if (size <= src_len)
		return (ft_strlen(src) + size);
	while (src[cur] && (src_len + cur) < (size - 1))
	{
		dst[src_len + cur] = src[cur];
		cur++;
	}
	dst[src_len + cur] = 0;
	return (ft_strlen(src) + src_len);
}

/*int main()
{
	char string[] = "Hello there, Venus";
    char buffer[19];
    int r;

	 r = ft_strlcpy(buffer,string,19);
	printf("Copied length is :%d", r);

    return(0);
}*/
