/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:37:48 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 16:58:10 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*get_name_of_line(char *line, t_list *garbage)
{
	int		i;
	char	*name;

	i = 0;
	while (line != NULL AND line[i] != EOS AND line[i] != '=')
		i += 1;
	name = ft_calloc(i + 1, sizeof(char), garbage);
	if (name == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '=')
	{
		name[i] = line[i];
		i += 1;
	}
	return (name);
}

char
	*get_value_of_line(char *line, t_list *garbage)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (line[j] && line[j] != '=')
		j++;
	value = ft_calloc(sizeof(char), ft_strlen(line) - j + 1, \
	garbage);
	if (!value)
		return (NULL);
	while (line[++j])
		value[i++] = line[j];
	return (value);
}

char
	*get_env_value(char *name, t_minishell *minishell)
{
	char	*value;
	int		line;

	value = NULL;
	line = find_line_of_name(minishell->environnement, name, \
	minishell->garbage);
	if (line == -1)
		return (NULL);
	value = get_value_of_line(minishell->environnement[line], \
	minishell->garbage);
	return (value);
}
