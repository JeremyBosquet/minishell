/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:40:02 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/18 15:39:52 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	check_numeric_argument(char **command)
{
	int		i;
	bool	num;

	i = 0;
	num = false;
	while (command[1][0] != EOS AND command[1][i] != EOS)
	{
		if (ft_isdigit(command[1][i]) == false)
		{
			printf("exit\n");
			error_exe(command[0], command[1], "numeric argument required", 255);
		}
		i += 1;
	}
	i = -1;
	while (command[1][0] != EOS AND command[1][++i] != EOS AND num == false)
		if (command[1][i] >= '0' AND command[1][i] <= '9')
			num = true;
	if (num != true)
	{
		printf("exit\n");
		error_exe(command[0], command[1], "numeric argument required", 255);
	}
}

void
	builtin_exit(t_minishell *minishell, int i)
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
		g_exit_code = ft_atoi(minishell->commands[i].command[1]) % 256;
		if (g_exit_code < 0)
			g_exit_code += 256;
	}
	else
		g_exit_code = 0;
	printf("exit\n");
	exit(g_exit_code);
}

void
	builtin_exit2(t_minishell *minishell, int i)
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
		g_exit_code = ft_atoi(minishell->commands[i].command[1]) % 256;
		if (g_exit_code < 0)
			g_exit_code += 256;
	}
	else
		g_exit_code = 0;
	exit(g_exit_code);
}
