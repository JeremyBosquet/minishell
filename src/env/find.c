/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:45:13 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 16:55:23 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env(char **env, char *name)
{
	int		i;
	// char	*tmp;

	i = 0;
	name = ft_strjoin(name, "=");
	// free(name);
	while (env[i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
		{
			// free(tmp);
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*get_env_name(char *line)
{
	int		j;
	char	*name;

	j = 0;
	while (line[j] != '=')
		j++;
	name = ft_calloc(sizeof(char), j + 1);
	if (!name)
		return (NULL);
	j = -1;
	while (line[++j] != '=')
		name[j] = line[j];
	name[j] = '=';
	return (name);
}

/*
int	find_env(char **env, char *name)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(name, "=");
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			free(name);
			return (i);
		}
		i++;
	}
	return (-1);
}
*/
