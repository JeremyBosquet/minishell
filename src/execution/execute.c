/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:27:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 10:09:33 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	execute_builtins(t_minishell *minishell, char *command)
{
	if (ft_strcmp(command, "exit") == 0 AND minishell->number_of_commands == 1)
		builtins_exit(minishell);
}

static void
	execute_command(char *command)
{
	(void) command;
}

void
	execute(t_minishell *minishell)
{
	int	i;
	int	j;

	if (minishell->number_of_commands != 0)
	{
		i = 0;
		while (i < minishell->number_of_commands)
		{
			j = 0;
			while (minishell->commands[i].command[j])
			{
				if (is_builtins(minishell->commands[i].command[j]) == true)
					execute_builtins(minishell, \
					minishell->commands[i].command[j]);
				else
					execute_command(minishell->commands[i].command[j]);
				j += 1;
			}
			i += 1;
		}
	}
}
