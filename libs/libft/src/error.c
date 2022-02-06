/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:44:06 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 16:45:44 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void
	error(char *message, int exit_status)
{
	fputstring(STDERR, RED);
	fputstring(STDERR, "error: ");
	fputstring(STDERR, END);
	fputstring(STDERR, message);
	fputchar(STDERR, '\n');
	exit(exit_status);
}
