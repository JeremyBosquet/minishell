/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:47:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 13:20:45 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	handle_signals(int signo)
{
	(void) signo;
	rl_replace_line("", 0);
	fputchar(STDERR, '\n');
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 1;
}

void
	signal_child(int signo)
{
	if (signo == SIGINT)
	{
		fputchar(STDERR, '\n');
		g_exit_code = 130;
	}
	else if (signo == SIGQUIT)
	{
		fputstring(STDERR, "Quit: 3\n");
		g_exit_code = 131;
	}
}

void
	signal_heredoc(int signo)
{
	(void) signo;
	fputchar(STDERR, '\n');
	g_exit_code = 1;
	exit(g_exit_code);
}

void
	my_signal(void)
{
	if (signal(SIGINT, handle_signals) == SIG_ERR \
	OR signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		error("bad signals", 1);
	g_exit_code = 1;
}
