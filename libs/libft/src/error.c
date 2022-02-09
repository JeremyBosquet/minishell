/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:44:06 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 15:35:32 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void
	print_error_message(char *message)
{
	fputstring(STDERR, ORANGE);
	fputstring(STDERR, "couscous: ");
	fputstring(STDERR, RED);
	fputstring(STDERR, "error: ");
	fputstring(STDERR, END);
	fputstring(STDERR, message);
	fputchar(STDERR, '\n');
}

void
	error(char *message, int exit_status)
{
	print_error_message(message);
	exit(exit_status);
}

int
	rerror(char *message, int return_code)
{
	print_error_message(message);
	return (return_code);
}

// void
// 	error_exe(char *command, int error_code)
// {
// 	print_error_message(command);
// }
