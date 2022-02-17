/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:00:48 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 13:20:45 by mmosca           ###   ########.fr       */
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
	free(minishell->current_pwd);
	return (true);
}
