/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:46:58 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:46:58 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	cur;
	int	num;
	int	sign;

	cur = 0;
	num = 0;
	sign = 1;
	while ((str[cur] >= 9 && str[cur] <= 13) || str[cur] == ' ')
		cur++;
	if (str[cur] == '+' || str[cur] == '-')
	{
		if (str[cur] == '-')
			sign = -1;
		cur++;
	}
	while (str[cur] >= '0' && str[cur] <= '9')
	{
		num = num * 10 + str[cur] - '0';
		cur++;
	}
	return (num * sign);
}

/* #include <stdio.h>

int main()
{
    int val;
    char strn1[] = "12546";

    val = ft_atoi(strn1);
    printf("String value = %s", strn1);
    printf("Integer value = %d", val);

    char strn2[] = "Hello Word";
    val = atoi(strn2);
    printf("String value = %s", strn2);
    printf("Integer value = %d", val);

    return (0);
}*/
