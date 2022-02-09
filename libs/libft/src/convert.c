/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:48:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 18:02:42 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_atoi(const char *string)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (string[i] == ' ' OR (string[i] >= '\t' AND string[i] <= '\r'))
		i += 1;
	if (string[i] == '-' OR string[i] == '+')
	{
		if (string[i] == '-')
			sign = -1;
		i += 1;
	}
	while (ft_isdigit(string[i]))
	{
		result = result * 10 + (string[i] - '0');
		if (result < 0 AND sign == -1)
			return (0);
		if (result < 0 AND sign == 1)
			return (-1);
		i += 1;
	}
	return (result * sign);
}
