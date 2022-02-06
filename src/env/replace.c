/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:58:37 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 16:27:27 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**replace_env(char **env, int line, char *value)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[line][i] != '=')
		i++;
	new_line = ft_calloc(sizeof(char), (i + ft_strlen(value) + 1));
	i = -1;
	while (env[line][++i] != '=')
		new_line[i] = env[line][i];
	new_line[i++] = '=';
	while (value[j])
		new_line[i++] = value[j++];
	free(env[line]);
	env[line] = ft_strdup(new_line);
	free(new_line);
	return (env);
}
