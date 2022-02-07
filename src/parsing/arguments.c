/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:34:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 10:05:13 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	check_number_of_argument(int number_of_arguments)
{
	if (number_of_arguments > 1)
		error("too many arguments", 1);
}
