/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:12:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 16:18:51 by mmosca           ###   ########.fr       */
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
	*ft_strrchr(const char *string, int character)
{
	int	i;

	i = ft_strlen(string) + 1;
	while (i--)
		if (string[i] == character)
			return ((char *) &string[i]);
	return (NULL);
}
