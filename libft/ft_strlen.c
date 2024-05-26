/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:51:54 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:51:54 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
