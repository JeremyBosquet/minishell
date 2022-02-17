/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 13:22:43 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 13:20:45 by mmosca           ###   ########.fr       */
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
	if ((character >= '0' AND character <= '9') || character == ' ')
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
