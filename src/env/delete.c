/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:59:58 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 16:51:58 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**delete_env(char **env, char *name)
{
	int		i;
	int		j;
	int		k;
	int		tmp;
	char	**new_env;

	i = 0;
	k = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(sizeof(char *), i);
	if (!new_env)
		return (NULL);
	j = 0;
	tmp = find_env(env, name);
	while (env[j])
	{
		if (j == tmp && j != i)
			j++;
		else
			new_env[k++] = ft_strdup(env[j++]);
	}
	free_array((void **) env, i);
	return (new_env);
}
