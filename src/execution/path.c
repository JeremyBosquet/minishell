/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:01:19 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/09 16:26:27 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	**raw_path(char **environnement)
{
	int		index;
	char	**path;

	index = 0;
	while (environnement[index] != (void *) 0 \
	AND ft_strnstr(environnement[index], "PATH=", PATH_MAX) == (void *) 0)
		index += 1;
	path = ft_split(((ft_strnchr(environnement[index], '=', 5)) + 1), ':');
	if (!path)
		return ((void *) 0);
	return (path);
}

static char
	**get_path(char **environnement)
{
	int		index;
	char	**path;

	index = 0;
	path = raw_path(environnement);
	if (!path)
		return ((void *) 0);
	while (path[index] != (void *) 0)
	{
		path[index] = ft_strfjoin(path[index], "/", 1);
		if (!path[index])
			return ((void *) 0);
		index += 1;
	}
	return (path);
}

char
	*check_path(char *command, char **environnement)
{
	int		index;
	char	**paths;
	char	*path;

	if (access(command, X_OK) == 0)
		return (command);
	index = 0;
	paths = get_path(environnement);
	if (!paths)
		exit(EXIT_FAILURE);
	while (paths[index] != (void *) 0)
	{
		paths[index] = ft_strfjoin(paths[index], command, 1);
		if (access(paths[index], X_OK) == 0)
		{
			path = ft_strndup(paths[index], ft_strlen(paths[index]) + 1);
			free_array((void **) paths, index);
			return (path);
		}
		index += 1;
	}
	free_array((void **) paths, index);
	return (NULL);
}
