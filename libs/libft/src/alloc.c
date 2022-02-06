/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:37:29 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 15:40:50 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(int count, int size)
{
	char	*string;

	string = malloc(count * size);
	if (string == NULL)
		return (NULL);
	return (ft_memset(string, 0, count * size));
}

void
	free_array(void **pointer, int size)
{
	int	i;

	i = 0;
	while (i < size AND pointer[i] != NULL)
	{
		free(pointer[i]);
		i += 1;
	}
	free(pointer);
}
