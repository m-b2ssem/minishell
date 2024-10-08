/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jseidere <jseidere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:48:57 by jkoupy            #+#    #+#             */
/*   Updated: 2024/04/19 20:59:44 by jseidere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*protection(const char *s1, const char *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (0);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*res;
	size_t	i;

	if (!s1 || !s2)
		return (protection(s1, s2));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (0);
	i = 0;
	while (i < (len1 + len2))
	{
		if (i < len1)
			res[i] = s1[i];
		else
			res[i] = s2[i - len1];
		i++;
	}
	res[i] = '\0';
	return (res);
}
