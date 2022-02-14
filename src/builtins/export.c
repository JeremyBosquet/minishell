/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:38:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/14 17:19:01 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	display_env(t_minishell *minishell, char **array)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (array[i] != NULL)
	{
		name = get_name_of_line(array[i], \
		minishell->garbage);
		value = get_value_of_line(array[i], \
		minishell->garbage);
		printf("declare -x %s=\"%s\"\n", name, value);
		i += 1;
		free(name);
		free(value);
	}
}

static int
	error_arg(char **command, int i)
{
	if (command[i][0] == '-')
	{
		printf("couscous: export: -%c: invalid option\n", command[i][1]);
		return (2);
	}
	else
	{
		printf("couscous: export: '%s': not a valid identifier\n", command[i]);
		return (1);
	}
}

static int
	check_arguments_or_options(t_minishell *minishell, char **command)
{
	char	*pos;
	int		i;

	i = 1;
	while (command[i] != NULL)
	{
		if (command[i][0] == '_' OR ft_isalpha(command[i][0]) == true)
		{
			pos = ft_strchr(command[i], '=');
			if (pos == NULL)
				return (0);
			minishell->environnement = add_to_environnement(\
		minishell->environnement, command[i], minishell->garbage);
		}
		else
			return (error_arg(command, i));
		i += 1;
	}
	return (0);
}

static void
	sort_ascii(char **command)
{
	int		i;
	int		size;
	bool	find;
	char	*tmp;

	size = size_of_array(command);
	find = true;
	while (find == true)
	{
		find = false;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(command[i], command[i + 1]) > 0)
			{
				tmp = command[i];
				command[i] = command[i + 1];
				command[i + 1] = tmp;
				find = true;
			}
			i += 1;
		}
	}
}

int
	builtin_export(t_minishell *minishell, int i)
{
	int		size_of_arg;
	int		check_arg;
	char	**tmp;

	size_of_arg = size_of_array(minishell->commands[i].command);
	if (size_of_arg < 2)
	{
		tmp = ft_dup_2array(minishell->environnement, minishell->garbage, 0);
		sort_ascii(tmp);
		display_env(minishell, tmp);
		free_array((void **) tmp, size_of_array(tmp));
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
