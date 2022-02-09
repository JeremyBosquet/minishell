/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:00:48 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 18:48:45 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool
	clean_minishell(t_minishell *minishell)
{
	free_array((void **) minishell->environnement, \
	size_of_array(minishell->environnement));
	list_clear(&minishell->garbage, free);
	rl_clear_history();
	return (true);
}
