/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:56:38 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 22:30:21 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**copy_environnement(char **environnement, int option, t_list *garbage)
{
	int		i;
	char	**new_environnement;

	i = size_of_array(environnement);
	new_environnement = ft_calloc(i + option + 1, sizeof(char *), \
	garbage);
	if (new_environnement == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	i = 0;
	while (environnement[i] != NULL)
	{
		new_environnement[i] = ft_calloc(ft_strlen(environnement[i]) + 1, \
		sizeof(char), garbage);
		if (new_environnement[i] == NULL)
			clean_environnement(environnement, size_of_array(environnement));
		ft_strcpy(new_environnement[i], environnement[i]);
		i += 1;
	}
	return (new_environnement);
}
