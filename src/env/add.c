/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:16:15 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 15:40:57 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_env(char	**env, char	*add_to_env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = -1;
	new_env = copy_env(env, 1);
	if (!new_env)
		return (NULL);
	while (new_env[i])
		i++;
	new_env[i] = malloc(sizeof(char) * ft_strlen(add_to_env) + 1);
	if (!new_env)
		return (NULL);
	while (add_to_env[++j])
		new_env[i][j] = add_to_env[j];
	new_env[i][j] = 0;
	new_env[i + 1] = 0;
	free_array((void **) env, i);
	return (new_env);
}
