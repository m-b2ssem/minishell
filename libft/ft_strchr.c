/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:50:16 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:50:16 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char) c == 0)
	{
		return ((char *)s);
	}
	return (NULL);
}

/*
#include <stdio.h>


int main () {
   const char str[] = "Hello word";
   const char ch = 'o';
   char *ret;

   ret = ft_strchr(str, ch);

   printf("String after is \n", ret);

   return(0);
}*/
