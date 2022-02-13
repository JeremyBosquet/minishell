/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:34:47 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/13 12:11:00 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static bool
	check_option(char **command)
{
	int	i;

	i = 1;
	if (command[1][0] == '-')
	{
		while (command[1][i] != EOS AND command[1][i] == 'n')
			i += 1;
		if (ft_strlen(command[1]) == i)
			return (true);
		else
			return (false);
	}
	return (false);
}

static void
	print_result(char **command, int size_of_command, int type)
{
	int	i;

	i = 1;
	if (type == 1)
	{
		while (command[++i] != NULL)
		{
			if (i == size_of_command - 1)
				printf("%s", command[i]);
			else
				printf("%s ", command[i]);
		}
	}
	if (type == 2)
	{
		while (command[i] != NULL)
		{
			if (i == size_of_command - 1)
				printf("%s\n", command[i]);
			else
				printf("%s ", command[i]);
			i += 1;
		}
	}
}

void
	builtin_echo(t_minishell *minishell, int i)
{
	int	size_of_cmd;

	size_of_cmd = size_of_array(minishell->commands[i].command);
	if (size_of_cmd < 2)
		printf("\n");
	else if (check_option(minishell->commands[i].command) == true)
		print_result(minishell->commands[i].command, size_of_cmd, 1);
	else
		print_result(minishell->commands[i].command, size_of_cmd, 2);
	exit(0);
}
