/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:35:03 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 19:26:25 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strncmp(const char *first_string, const char *second_string, int size)
{
	int	i;

	if (size == 0)
		return (0);
	i = 0;
	while (first_string[i] != EOS AND second_string[i] != EOS \
	AND first_string[i] == second_string[i] AND i < size - 1)
		i += 1;
	return ((unsigned char)first_string[i] - (unsigned char)second_string[i]);
}

char
	*ft_strncpy(char *destination, char *source, int size)
{
	int	i;

	i = 0;
	while (source[i] != EOS AND i < size)
	{
		destination[i] = source[i];
		i += 1;
	}
	while (i < size)
	{
		destination[i] = EOS;
		i += 1;
	}
	return (destination);
}

char
	*ft_strndup(const char *string, int size)
{
	char	*new;

	new = ft_calloc(size, sizeof(char));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, string, size);
	return (new);
}

char
	*ft_strnstr(const char *string, const char *to_find, int size)
{
	int	i;
	int	j;

	if (to_find[0] == EOS)
		return ((char *) string);
	i = 0;
	while (string[i] != EOS AND i < size)
	{
		j = 0;
		while (to_find[j] != EOS AND string[i + j] == to_find[j] \
		AND i + j < size)
			j += 1;
		if (to_find[j] == EOS)
			return ((char *) &string[i]);
		i += 1;
	}
	return (NULL);
}
