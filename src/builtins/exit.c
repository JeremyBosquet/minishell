/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 15:41:08 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void
	builtins_exit(t_minishell *minishell)
{
	minishell->is_running = false;
	minishell->exit_code = 0;
}
