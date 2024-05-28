/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:57:41 by amirfatt          #+#    #+#             */
/*   Updated: 2024/05/28 14:57:41 by amirfatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_vars_modif(int *here, char *j)
{
	*here = 0;
	if (j == NULL)
		return (1);
	return (0);
}

char	*my_strcat(char *destination, const char *source)
{
	char	*temp;

	temp = destination;
	while (*destination)
		destination++;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return (temp);
}

int	strcmp_custom(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

char	*strcpy_custom(char *destination, const char *source)
{
	char	*temp;

	temp = destination;
	while (*source)
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	return (temp);
}

void	cleanup_on_error(t_token **head, char **arr, int i)
{
	t_token	*tmp;

	while (*head)
	{
		tmp = (*head);
		(*head) = (*head)->next;
		free(tmp->string);
		free(tmp);
	}
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
