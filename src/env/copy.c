/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:56:38 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 15:48:12 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**copy_env2(char **envp, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = -1;
		while (envp[i][++j])
			env[i][j] = envp[i][j];
		i++;
	}
	return (env);
}

char	**copy_env(char **envp, int opt)
{
	int		i;
	int		j;
	char	**env;

	i = 0;
	while (envp[i])
		i++;
	env = ft_calloc(sizeof(char *), (i + 1 + opt));
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
			j++;
		env[i] = ft_calloc(sizeof(char), j + 1);
		if (!env[i])
			return (NULL);
		i++;
	}
	return (copy_env2(envp, env));
}
