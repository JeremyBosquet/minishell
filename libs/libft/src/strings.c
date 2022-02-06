/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:16:03 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 18:49:52 by mmosca           ###   ########.fr       */
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
	*ft_strdup(const char *string)
{
	char	*new;
	int		size;

	size = ft_strlen(string) + 1;
	new = ft_calloc(size, sizeof(char));
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
