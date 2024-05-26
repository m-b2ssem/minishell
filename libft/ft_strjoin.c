/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:51:17 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:51:17 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*joining;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	joining = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!joining)
		return (NULL);
	ft_strlcpy(joining, s1, s1_len + 1);
	ft_strlcpy((joining + s1_len), s2, s2_len + 1);
	return (joining);
}
