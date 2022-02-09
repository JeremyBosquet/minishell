/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:12:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 16:17:26 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strchr(const char *string, int character)
{
	int	i;

	i = 0;
	while (string[i] != EOS)
	{
		if (string[i] == character)
			return ((char *) &string[i]);
		i += 1;
	}
	if (string[i] == character)
		return ((char *) &string[i]);
	return (NULL);
}

char
	*ft_strnchr(char *string, char character, int number)
{
	int	index;

	index = 0;
	while (string[index] != '\0' && string[index] != character \
	&& index < number)
		index += 1;
	if (string[index] == character && index != number)
		return (string + index);
	return (NULL);
}

char
	*ft_strrchr(const char *string, int character)
{
	int	i;

	i = ft_strlen(string) + 1;
	while (i--)
		if (string[i] == character)
			return ((char *) &string[i]);
	return (NULL);
}
