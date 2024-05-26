/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:47:27 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/26 17:47:27 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	cur;
	char	*data;

	cur = 0;
	data = s;
	while (cur < n)
	{
		data[cur] = 0;
		cur++;
	}
}

/* #include <stdio.h>

int main() {
    // Define an array of characters
    char str[] = "Hello, World!";

    // Display the original string
    printf("Original String: %s\n", str);

    // Use ft_memset to fill the string with 'X' from index 6 to 11
    ft_bzero(str + 6, 5);

    // Display the modified string
    printf("Modified String: %s\n", str);

    return 0;
}*/
