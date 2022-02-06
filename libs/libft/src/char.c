/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:22:43 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 13:32:55 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool
	ft_isalnum(int character)
{
	if (ft_isalpha(character) OR ft_isdigit(character))
		return (true);
	return (false);
}

bool
	ft_isalpha(int character)
{
	if ((character >= 'A' AND character <= 'Z') \
	OR (character >= 'a' AND character <= 'z'))
		return (true);
	return (false);
}

bool
	ft_isascii(int character)
{
	if (character >= 0 AND character <= 127)
		return (true);
	return (false);
}

bool
	ft_isdigit(int character)
{
	if (character >= '0' AND character <= '9')
		return (true);
	return (false);
}

bool
	ft_isprintable(int character)
{
	if (character >= ' ' AND character <= '~')
		return (true);
	return (false);
}
