/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:21:57 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 15:16:54 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		tmp = ft_strdup(minishell->current_pwd, minishell->garbage);
	oldpwd = ft_strfjoin(oldpwd, tmp, 3, minishell->garbage);
	if (oldpwd == NULL)
		return (false);
	minishell->environnement = add_to_environnement(minishell->environnement, \
	oldpwd, minishell->garbage);
	minishell->env_export = add_to_export(minishell->env_export, oldpwd, \
	minishell->garbage);
	free(oldpwd);
	return (true);
}

static int
	check_bi_cd(t_minishell *minishell, int i)
{
	if (size_of_array(minishell->commands[i].command) < 2 \
	OR set_oldpwd(minishell) == false)
		return (0);
	if (check_option(minishell->commands[i].command) == true)
		return (1);
	if (chdir(minishell->commands[i].command[1]) != 0)
	{
		printf("couscous: %s: No such file or directory\n", \
		minishell->commands[i].command[1]);
		return (1);
	}
	return (-1);
}

static void
	add_env_export(t_minishell *minishell, char *path)
{
	minishell->environnement = add_to_environnement(\
	minishell->environnement, path, minishell->garbage);
	minishell->env_export = add_to_export(\
	minishell->env_export, path, minishell->garbage);
}

int
	builtin_cd(t_minishell *minishell, int i)
{
	char	*path;
	char	*tmp;
	int		ret;

	ret = check_bi_cd(minishell, i);
	if (ret != -1)
		return (ret);
	path = ft_strdup("PWD=", minishell->garbage);
	if (path == NULL)
		return (0);
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		tmp = ft_strdup(minishell->current_pwd, minishell->garbage);
	else
	{
		free(minishell->current_pwd);
		minishell->current_pwd = ft_strdup(tmp, minishell->garbage);
	}
	path = ft_strfjoin(path, tmp, 3, minishell->garbage);
	if (path == NULL)
		return (0);
	add_env_export(minishell, path);
	free(path);
	return (0);
}
