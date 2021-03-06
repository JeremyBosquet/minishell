/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:24:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 15:04:49 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	check_first_char(char **command)
{
	if (command[1][0] != '_' AND ft_isalpha(command[1][0]) == false)
	{
		printf("couscous: unset: %s: not a valid identifer\n", command[1]);
		return (1);
	}
	else if (command[1][0] == '-')
	{
		printf("couscous: unset: -%c: invalid option\n", command[1][1]);
		return (2);
	}
	return (0);
}

static int
	check_arguments_or_options(char **command)
{
	int	i;
	int	j;
	int	check_char;

	check_char = check_first_char(command);
	if (check_char == 1 || check_char == 2)
		return (check_char);
	i = 1;
	while (command[i] != NULL)
	{
		j = 0;
		while (command[i][j] != EOS)
		{
			if (command[i][0] != '_' AND ft_isalpha(command[i][0]) == false)
			{
				printf("couscous: unset: %s: not a valid identifer\n", \
				command[i]);
				return (1);
			}
			j += 1;
		}
		i += 1;
	}
	return (0);
}

int
	builtin_unset(t_minishell *minishell, int i)
{
	int		j;
	int		size_of_arg;
	int		return_value;

	size_of_arg = size_of_array(minishell->commands[i].command);
	if (size_of_arg < 2)
		return (0);
	return_value = check_arguments_or_options(minishell->commands[i].command);
	if (return_value == 1 OR return_value == 2)
		return (return_value);
	j = 0;
	while (++j < size_of_arg)
	{
		if (ft_strcmp(minishell->commands[i].command[j], "PWD") == 0)
		{
			minishell->environnement = delete_line_in_environnement(\
			minishell->environnement, "OLDPWD", minishell->garbage);
		}
		minishell->environnement = delete_line_in_environnement(\
	minishell->environnement, minishell->commands[i].command[j], \
	minishell->garbage);
		minishell->env_export = delete_line_in_export(minishell->env_export, \
		minishell->commands[i].command[j], minishell->garbage);
	}
	return (0);
}
