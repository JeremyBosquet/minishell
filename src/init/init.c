/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:30:01 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 17:33:16 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	init_minishell(t_minishell *minishell, char	**envp)
{
	minishell->cmds = NULL;
	minishell->nb_cmds = 0;
	minishell->env = copy_env(envp, 0);
	minishell->last_exit_code = 0;
	minishell->is_running = true;
	return (true);
}
