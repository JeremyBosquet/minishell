/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:45:13 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 19:14:54 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	find_line_of_name(char **environnement, char *name)
{
	int	i;

	name = ft_strjoin(name, "=");
	i = 0;
	while (environnement[i] != NULL)
	{
		if (ft_strncmp(environnement[i], name, ft_strlen(name)) == 0)
			return (i);
		i += 1;
	}
	return (-1);
}
