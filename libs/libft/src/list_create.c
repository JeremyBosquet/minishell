/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:20:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 18:30:40 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	list_add_back(t_list **list, t_list *new)
{
	t_list	*tmp;

	tmp = *list;
	if (tmp == NULL)
		*list = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void
	list_add_front(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
}

t_list
	*list_new(void *content)
{
	t_list	*new;

	new = malloc(1 * sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}
