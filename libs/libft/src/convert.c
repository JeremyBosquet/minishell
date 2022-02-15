/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:48:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/15 10:36:45 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long
	ft_atoi(const char *string)
{
	int		i;
	long	result;
	int		sign;

	i = 0;
	result = 0;
	sign = 1;
	while (string[i] == ' ' OR (string[i] >= '\t' AND string[i] <= '\r'))
		i += 1;
	if (string[i] == '-' OR string[i] == '+')
		if (string[i++] == '-')
			sign = -1;
	while (ft_isdigit(string[i]))
	{
		result = result * 10 + (string[i] - '0');
		if (result < 0)
		{
			printf("exit\ncouscous: exit: %ld: numeric argument required\n", \
			result);
			return (-1);
		}
		i += 1;
	}
	return (result * sign);
}
