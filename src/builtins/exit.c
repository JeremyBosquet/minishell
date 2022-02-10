/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 13:22:57 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

/*
 * Si tu as un argument qui est plus grand de 256 alors faut retirer 256
 * a l'argument passer en parametre
 */
void
	builtins_exit(t_minishell *minishell, int i)
{
	// Faire attention car il print le exit mais n'exit pas du prog.
	if (minishell->commands[i].command[1] != NULL)
	{
		minishell->exit_code = ft_atoi(minishell->commands[i].command[1]);
		while (minishell->exit_code > 255)
			minishell->exit_code -= 256;
	}
	else
		minishell->exit_code = 0;
	minishell->is_running = false;
}
