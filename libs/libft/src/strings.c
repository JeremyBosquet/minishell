/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:16:03 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 17:59:10 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	while (string != NULL AND string[i] != EOS)
		i += 1;
	return (i);
}

char
	*ft_strdup(const char *string, t_list *garbage)
{
	char	*new;
	int		size;

	size = ft_strlen(string) + 1;
	new = ft_calloc(size, sizeof(char), garbage);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, string, size);
	return (new);
}

char
	*ft_strcpy(char *destination, char *source)
{
	int	i;

	i = 0;
	while (source[i] != '\0')
	{
		destination[i] = source[i];
		i += 1;
	}
	destination[i] = '\0';
	return (destination);
}

int
	ft_strcmp(char *first_string, char *second_string)
{
	int	i;

	i = 0;
	while (first_string[i] != EOS AND second_string[i] != EOS \
	AND first_string[i] == second_string[i])
		i += 1;
	return (first_string[i] - second_string[i]);
}
