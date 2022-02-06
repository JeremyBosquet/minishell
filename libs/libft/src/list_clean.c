/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:31:40 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 16:37:07 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	list_clear(t_list **list, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *list;
	if (tmp == NULL)
		return ;
	while (tmp->next != NULL)
	{
		tmp2 = tmp->next;
		list_delone(tmp, del);
		tmp = tmp2;
	}
	list_delone(tmp, del);
	*list = NULL;
}

void
	list_delone(t_list *list, void (*del)(void *))
{
	del(list->content);
	free(list);
}
