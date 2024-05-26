/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:48:56 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:48:56 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		uc;
	const unsigned char	*src;

	uc = c;
	src = s;
	while (n > 0)
	{
		if (*src == uc)
		{
			return ((void *)src);
		}
		src++;
		n--;
	}
	return (0);
}
