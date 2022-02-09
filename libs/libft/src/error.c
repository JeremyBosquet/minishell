/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:44:06 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 16:15:08 by jbosquet         ###   ########.fr       */
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

// void
// 	error_exe(char *command, int error_code)
// {
// 	print_error_message(command);
// }
