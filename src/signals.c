/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:47:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 11:37:41 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	handle_signals(int signo)
{
	(void) signo;
	// kill ?
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void
	my_signal(void)
{
	if (signal(SIGINT, handle_signals) == SIG_ERR)
		error("bad signals", 1);
}
