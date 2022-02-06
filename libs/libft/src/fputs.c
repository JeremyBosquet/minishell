/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fputs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:05:39 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 15:04:18 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	fputchar(int filedescriptor, char character)
{
	write(filedescriptor, &character, 1);
}

void
	fputnbr(int filedescriptor, int number)
{
	unsigned int	unumber;

	if (ft_isnegative(number) == true)
	{
		fputchar(filedescriptor, '-');
		unumber = (-number);
	}
	else
		unumber = number;
	if (unumber > 9)
		fputnbr(filedescriptor, unumber / 10);
	fputchar(filedescriptor, unumber % 10 + '0');
}

void
	fputstring(int filedescriptor, char *string)
{
	if (string == NULL)
		return ;
	write(filedescriptor, string, ft_strlen(string));
}
