/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:41:36 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/12 15:38:55 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool
	init_minishell(t_minishell *minishell, char	**envp)
{
	minishell->commands = NULL;
	minishell->pids = NULL;
	minishell->number_of_commands = 0;
	minishell->garbage = NULL;
	minishell->environnement = copy_environnement(envp, 0, \
	minishell->garbage);
	minishell->exit_code = 0;
	minishell->is_running = true;
	return (true);
}
