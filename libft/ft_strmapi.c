/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:52:02 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:52:02 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == 0)
		return (NULL);
	while (i < len)
	{
		res[i] = (*f)(i, s[i]);
		++i;
	}
	res[i] = '\0';
	return (res);
}

/* #include <stdio.h>
char f(unsigned int i, char c)
{
	char str;
	str = c + 1;
	return (str);
}

int main()
{
	char str1[] = "abc";
	char* str2;
str2 = ft_strmapi(str1, *f);
	printf("%s\n", str2);
}*/
