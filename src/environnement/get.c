/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:37:48 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 10:42:27 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*get_name_of_line(char *line)
{
	int		i;
	char	*name;

	i = 0;
	while (line != NULL AND line[i] != EOS AND line[i] != '=')
		i += 1;
	name = ft_calloc(i + 1, sizeof(char));
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
	*get_value_of_line(char *line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (line != NULL AND line[i] != EOS AND line[i] != '=')
		i += 1;
	i += 1;
	value = ft_calloc(ft_strlen(line) - i, sizeof(char));
	if (value == NULL)
		return (NULL);
	j = 0;
	while (line[i] != EOS)
	{
		value[j] = line[i];
		i += 1;
		j += 1;
	}
	return (value);
}
