/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:21:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/13 15:19:49 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static bool
	check_option(char **command)
{
	if (command[1][0] == '-')
	{
		printf("couscous: cd: -%c: invalid option\n", command[1][1]);
		return (true);
	}
	return (false);
}

int
	builtin_cd(t_minishell *minishell, int i)
{
	char	*path;
	char	*tmp;

	if (size_of_array(minishell->commands[i].command) < 2)
		return (0);
	if (check_option(minishell->commands[i].command) == true)
		return (1);
	if (chdir(minishell->commands[i].command[1]) != 0)
	{
		printf("couscous: %s: No such file or directory\n", \
		minishell->commands[i].command[1]);
		return (errno);
	}
	path = ft_strdup("PWD=", minishell->garbage);
	if (path == NULL)
		return (0);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (0);
	path = ft_strfjoin(path, tmp, 3, minishell->garbage);
	if (path == NULL)
		return (0);
	minishell->environnement = add_to_environnement(\
	minishell->environnement, path, minishell->garbage);
	return (0);
}
