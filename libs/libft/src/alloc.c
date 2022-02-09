/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:37:29 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 18:51:34 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	*ft_calloc(int count, int size, t_list *garbage)
{
	char	*string;
	t_list	*tmp;

	string = malloc(count * size);
	if (string == NULL)
		return (NULL);
	tmp = list_new(string);
	list_add_front(&garbage, tmp);
	free(tmp);
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
