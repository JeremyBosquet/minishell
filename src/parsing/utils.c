/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 22:04:09 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/16 22:32:22 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	init_fd_command(t_minishell *minishell, int i)
{
	minishell->commands[i].fd_in = STDIN;
	minishell->commands[i].fd_out = STDOUT;
	minishell->commands[i].do_open_in = true;
	minishell->commands[i].do_open_out = true;
	minishell->commands[i].file_in = NULL;
	minishell->commands[i].file_out = NULL;
	minishell->commands[i].do_run = true;
	minishell->commands[i].type_infile = -1;
	minishell->commands[i].type_outfile = -1;
}
