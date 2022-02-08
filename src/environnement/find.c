/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:45:13 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/08 10:54:38 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	find_line_of_name(char **environnement, char *name)
{
	int		i;
	char	*tmp;

	tmp = ft_calloc(ft_strlen(name) + 1, sizeof(char));
	if (tmp == NULL)
		error("out of memory!", 1);
	ft_strcpy(tmp, name);
	name = ft_strjoin(tmp, "=");
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
