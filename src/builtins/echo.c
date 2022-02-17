/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 11:34:47 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 13:20:45 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool
	check_option(char **command)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (command[j] != NULL)
	{
		if (command[j][0] == '-')
		{
			while (command[j][i] != EOS AND command[j][i] == 'n')
				i += 1;
			if (ft_strlen(command[j]) == i)
				return (true);
			else
				return (false);
		}
		if (command[j][0] == '>' || command[j][0] == '<')
			return (true);
		j += 1;
	}
	return (false);
}

static int
	get_how_mani_option(char **command)
{
	int	i;
	int	j;
	int	nb_option;

	i = 1;
	j = 1;
	nb_option = 0;
	while (command[j] != NULL)
	{
		if (command[j][0] == '-')
		{
			while (command[j][i] != EOS AND command[j][i] == 'n')
				i += 1;
			if (ft_strlen(command[j]) == i)
				nb_option += 1;
		}
		j += 1;
	}
	return (nb_option);
}

static void
	print_result(char **command, int size_of_command, int type)
{
	int	i;

	i = 1;
	if (type == 0)
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
	else if (type > 0)
	{
		i = type;
		while (command[++i] != NULL)
		{
			if (i == size_of_command - 1)
				printf("%s", command[i]);
			else
				printf("%s ", command[i]);
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
		print_result(minishell->commands[i].command, size_of_cmd, \
		get_how_mani_option(minishell->commands[i].command));
	else
		print_result(minishell->commands[i].command, size_of_cmd, 0);
	exit(0);
}
