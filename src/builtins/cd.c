/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:21:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/13 16:37:22 by mmosca           ###   ########.fr       */
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

static bool
	set_oldpwd(t_minishell *minishell)
{
	char	*oldpwd;
	char	*tmp;

	oldpwd = ft_strdup("OLDPWD=", minishell->garbage);
	if (oldpwd == NULL)
		return (false);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (false);
	oldpwd = ft_strfjoin(oldpwd, tmp, 3, minishell->garbage);
	if (oldpwd == NULL)
		return (false);
	minishell->environnement = add_to_environnement(minishell->environnement, \
	oldpwd, minishell->garbage);
	free(oldpwd);
	return (true);
}

static int
	error_message(int errnumber, char *command)
{
	printf("couscous: %s: No such file or directory\n", command);
	return (errnumber);
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
	if (set_oldpwd(minishell) == false)
		return (0);
	if (chdir(minishell->commands[i].command[1]) != 0)
		error_message(errno, minishell->commands[i].command[1]);
	path = ft_strdup("PWD=", minishell->garbage);
	tmp = getcwd(NULL, 0);
	if (path == NULL OR tmp == NULL)
		return (0);
	path = ft_strfjoin(path, tmp, 3, minishell->garbage);
	if (path == NULL)
		return (0);
	minishell->environnement = add_to_environnement(\
	minishell->environnement, path, minishell->garbage);
	free(path);
	return (0);
}
