/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/11 16:10:43 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	check_numeric_argument(char **command)
{
	int	i;

	i = 1;
	while (command[1][i] != EOS)
	{
		if (ft_isdigit(command[1][i]) == false)
		{
			printf("exit\n");
			error_exe(command[0], command[1], "numeric argument required", 255);
		}
		i += 1;
	}
}

void
	builtins_exit(t_minishell *minishell, int i)
{
	int		nb_args;

	nb_args = size_of_array(minishell->commands[i].command);
	if (minishell->commands[i].command[1] != NULL)
	{
		check_numeric_argument(minishell->commands[i].command);
		if (nb_args > 2)
		{
			printf("exit\ncouscous: too many arguments\n");
			return ;
		}
		minishell->exit_code = ft_atoi(minishell->commands[i].command[1]) % 256;
		if (minishell->exit_code < 0)
			minishell->exit_code += 256;
	}
	else
		minishell->exit_code = 0;
	exit(minishell->exit_code);
}
