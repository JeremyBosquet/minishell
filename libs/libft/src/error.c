/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:44:06 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 13:13:15 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void
	print_error_message(char *prefix, char *message)
{
	fputstring(STDERR, ORANGE);
	fputstring(STDERR, "couscous: ");
	fputstring(STDERR, RED);
	fputstring(STDERR, prefix);
	fputstring(STDERR, END);
	fputstring(STDERR, message);
	fputchar(STDERR, '\n');
}

void
	error(char *message, int exit_status)
{
	print_error_message("error: ", message);
	exit(exit_status);
}

int
	rerror(char *prefix, char *message, int return_code)
{
	print_error_message(prefix, message);
	return (return_code);
}

void
	error_exe(char *command, char *arg, char *message, int error_code)
{
	fputstring(STDERR, "couscous: ");
	fputstring(STDERR, command);
	fputstring(STDERR, ": ");
	fputstring(STDERR, arg);
	fputstring(STDERR, ": ");
	fputstring(STDERR, message);
	fputchar(STDERR, '\n');
	exit(error_code);
}
