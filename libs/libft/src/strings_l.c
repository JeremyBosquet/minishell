/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:12:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 15:33:13 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strlcat(char *destination, const char *source, int size)
{
	int	i;
	int	j;

	i = 0;
	while (destination[i] != EOS AND i < size)
		i += 1;
	j = 0;
	while (source[j] != EOS AND i + j + 1 < size)
	{
		destination[i + j] = source[j];
		j += 1;
	}
	if (i != size)
		destination[i + j] = EOS;
	return (ft_strlen(source) + 1);
}

int
	ft_strlcpy(char *destination, const char *source, int size)
{
	int	i;
	int	source_length;

	source_length = ft_strlen(source);
	if (source_length == 0)
	{
		destination = NULL;
		return (0);
	}
	if (size == 0)
		return (source_length);
	i = 0;
	while (source[i] != EOS AND i < size - 1)
	{
		destination[i] = source[i];
		i += 1;
	}
	destination[i] = EOS;
	return (source_length);
}
