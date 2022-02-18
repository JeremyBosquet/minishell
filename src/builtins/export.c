/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 10:38:54 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/18 15:47:44 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	display_env(t_minishell *minishell, char **array)
{
	int		i;
	char	*name;
	char	*value;

	i = 0;
	while (array[i] != NULL)
	{
		if (ft_strchr(array[i], '=') == NULL)
			printf("declare -x %s\n", array[i++]);
		else
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
		if (array[i] == NULL)
			break ;
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
	int	i;

	i = 0;
	while (command[++i] != NULL)
	{
		if (command[i][0] == '_' OR ft_isalpha(command[i][0]) == true)
		{
			if (ft_strchr(command[i], '=') == NULL)
				minishell->env_export = add_to_export(minishell->env_export, \
				command[i], minishell->garbage);
			else
			{
				minishell->environnement = add_to_environnement(\
				minishell->environnement, command[i], minishell->garbage);
				minishell->env_export = add_to_export(\
				minishell->env_export, command[i], minishell->garbage);
			}
		}
		else
			return (error_arg(command, i));
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
	int		size;
	int		check;

	size = size_of_array(minishell->commands[i].command);
	if (size == 1)
	{
		if (find_line_of_name2(minishell->env_export, "OLDPWD") == -1)
			minishell->env_export = add_to_export(minishell->env_export, \
			"OLDPWD", minishell->garbage);
		sort_ascii(minishell->env_export);
		display_env(minishell, minishell->env_export);
		return (0);
	}
	else
	{
		check = check_arguments_or_options(minishell, \
		minishell->commands[i].command);
		if (check == 1 OR check == 2)
			return (check);
		return (0);
	}
}
