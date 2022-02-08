/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 15:59:58 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/08 12:06:49 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**delete_line_in_environnement(char **environnement, char *name)
{
	int		i;
	int		j;
	int		size;
	char	**new_environnement;

	size = size_of_array(environnement);
	new_environnement = ft_calloc(size + 1, sizeof(char));
	if (new_environnement == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (environnement[i] != NULL)
	{
		if (i == find_line_of_name(environnement, name) AND i != size)
			i += 1;
		else
			new_environnement[j++] = ft_strdup(environnement[i++]);
	}
	free_array((void **) environnement, size);
	return (new_environnement);
}
