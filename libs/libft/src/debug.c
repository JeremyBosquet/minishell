/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:47:04 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 10:28:07 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	print_debug(char *value, int line, char *file)
{
	dprintf(2, PURPLE"%s: %d: "END"%s\n", file, line, value);
}
