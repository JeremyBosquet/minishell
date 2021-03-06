/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:45:13 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/17 14:00:50 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	find_line_of_name(char **environnement, char *name, t_list *garbage)
{
	int		i;
	char	*tmp;

	tmp = ft_calloc(ft_strlen(name) + 1, sizeof(char), garbage);
	if (tmp == NULL)
		error("out of memory!", 1);
	ft_strcpy(tmp, name);
	name = ft_strjoin(tmp, "=", garbage);
	free(tmp);
	i = 0;
	while (environnement[i] != NULL)
	{
		if (ft_strncmp(environnement[i], name, ft_strlen(name)) == 0)
		{
			free(name);
			return (i);
		}
		i += 1;
	}
	free(name);
	return (-1);
}

int
	find_line_of_name2(char **environnement, char *name)
{
	int	i;

	i = 0;
	while (environnement[i] != NULL)
	{
		if (ft_strncmp(environnement[i], name, ft_strlen(name)) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}
