/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 15:42:07 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void
	builtins_exit(t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (minishell->commands[i].command[j])
		j += 1;
	if (j > 2)
	{
		printf("exit\ncouscous: exit: too many arguments\n");
		return ;
	}
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
