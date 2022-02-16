/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/16 22:21:26 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	return_value_after_quote(const char *string, int i)
{
	int		tmp;
	char	type;

	type = string[i];
	tmp = i;
	i++;
	while (string[i] != 0 && string[i] != type)
		i++;
	return (i - tmp + 1);
}

int
	wlength2(const char *string, int *length)
{
	if (string[*length + 1] == '<')
		*length += 2;
	else
	{
		if (string[*length + 1] != '>')
			*length += 1;
		else if (string[*length + 1] == '>')
			*length += 1;
	}
	return (*length);
}

int
	wlength3(const char *string, int *length)
{
	if (string[*length + 1] == '>')
		*length += 2;
	else
		if (string[*length + 1] != '<')
			*length += 1;
	return (*length);
}
