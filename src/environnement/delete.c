/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:59:58 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 19:13:16 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**delete_line_in_environnement(char **environnement, char *name)
{
	int		i;
	int		j;
	int		size;
	int		line;
	char	**new_environnement;

	size = size_of_array(environnement);
	new_environnement = ft_calloc(size, sizeof(char));
	if (new_environnement == NULL)
		return (NULL);
	line = find_line_of_name(environnement, name);
	i = 0;
	j = 0;
	while (environnement[i] != NULL)
	{
		if (i == line AND i != size)
			i += 1;
		else
		{
			new_environnement[j] = ft_strdup(environnement[i]);
			i += 1;
		}
	}
	free_array((void **) environnement, size);
	return (new_environnement);
}
