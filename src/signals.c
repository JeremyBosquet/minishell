/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:47:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/14 14:15:53 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	handle_signals(int signo)
{
	(void) signo;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void
	my_signal(void)
{
	if (signal(SIGINT, handle_signals) == SIG_ERR \
	OR signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error("bad signals", 1);
}

//signal(SIGKILL, SIG_IGN); ignorer dans le parent
//signal(SIGKILL, NULL); remettre a l'etat de base dans l'enfant
//signal(SIGKILL, sighandler);
