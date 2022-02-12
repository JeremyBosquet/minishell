/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:38:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/12 16:08:00 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	display_env(t_minishell *minishell)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (minishell->environnement[i] != NULL)
	{
		name = get_name_of_line(minishell->environnement[i], \
		minishell->garbage);
		value = get_value_of_line(minishell->environnement[i], \
		minishell->garbage);
		printf("declare -x %s=\"%s\"\n", name, value);
		free(name);
		free(value);
		i += 1;
	}
}

static int
	check_arguments_or_options(t_minishell *minishell, char **command)
{
	char	*pos;

	if (command[1][0] == '_' OR ft_isalpha(command[1][0]) == true)
	{
		pos = ft_strchr(command[1], '=');
		if (pos == NULL)
			return (0);
		minishell->environnement = add_to_environnement(\
		minishell->environnement, command[1], minishell->garbage);
		return (0);
	}
	else
	{
		if (command[1][0] == '-')
		{
			printf("couscous: export: -%c: invalid option\n", command[1][1]);
			return (2);
		}
		else
		{
			printf("couscous: export: '%s': not a valid identifier\n", \
			command[1]);
			return (1);
		}
	}
}

int
	builtin_export(t_minishell *minishell, int i)
{
	int	size_of_arg;
	int	check_arg;

	size_of_arg = size_of_array(minishell->commands[i].command);
	if (size_of_arg < 2)
	{
		display_env(minishell);
		return (0);
	}
	else
	{
		check_arg = check_arguments_or_options(minishell, \
		minishell->commands[i].command);
		if (check_arg == 1 || check_arg == 2)
			return (check_arg);
		return (0);
	}
}
