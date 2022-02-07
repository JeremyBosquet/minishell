/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:00:48 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 20:32:21 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool
	clean_minishell(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->number_of_commands)
	{
		free_array((void **)minishell->commands[i].command, size_of_array(minishell->commands[i].command));	
		i++;
	}
	free(minishell->commands);
	free_array((void **) minishell->environnement, \
	size_of_array(minishell->environnement));
	rl_clear_history();
	return (true);
}
