/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:47:04 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 09:48:28 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	print_debug(int line, char *file)
{
	dprintf(2, PURPLE"%s:%d "END"this is a debug message!\n", file, line);
}

void
	print_debug_str(char *value, int line, char *file)
{
	dprintf(2, PURPLE"%s:%d "END"%s\n", file, line, value);
}

void
	print_debug_int(int value, int line, char *file)
{
	dprintf(2, PURPLE"%s:%d "END"%d\n", file, line, value);
}
