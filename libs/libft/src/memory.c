/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:39:49 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 16:49:51 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_memcpy(void *destination, const void *source, int size)
{
	void	*dest;

	if (destination == NULL OR source == NULL)
		return (NULL);
	dest = destination;
	while (size--)
	{
		*(unsigned char *) destination = *(unsigned char *) source;
		destination += 1;
		source += 1;
	}
	return (dest);
}

void
	*ft_memmove(void *destination, const void *source, int size)
{
	if (destination == NULL OR source == NULL)
		return (NULL);
	if (destination < source)
		ft_memcpy(destination, source, size);
	else
		while (size--)
			*(unsigned char *)(destination + size) \
			= *(unsigned char *)(source + size);
	return (destination);
}

void
	*ft_memset(void *buffer, int character, int length)
{
	void	*tmp;

	tmp = buffer;
	while (length--)
	{
		*(unsigned char *) buffer = (unsigned char) character;
		buffer += 1;
	}
	return (tmp);
}
