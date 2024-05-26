/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:49:11 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:49:11 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
