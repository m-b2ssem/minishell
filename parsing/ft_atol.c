/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:25:27 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/31 12:26:51 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long	ft_atol(const char *str)
{
	long	result;
	long	sign;
	size_t	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if ((sign == -1 && i > 20) || (sign == 1 && i > 19)
			|| result > LONG_MAX || result < LONG_MIN)
			return (-1);
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}
