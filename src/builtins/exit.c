/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 16:10:31 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

/*
 * Si tu as un argument qui est plus grand de 256 alors faut retirer 256
 * a l'argument passer en parametre
 */
void
	builtins_exit(t_minishell *minishell)
{
	minishell->is_running = false;
	minishell->exit_code = 0;
}
