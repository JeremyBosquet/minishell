/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 12:56:38 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 19:11:27 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**copy_environnement(char **environnement, int option)
{
	int		i;
	int		j;
	char	**new_environnement;

	i = size_of_array(environnement);
	new_environnement = ft_calloc(i + option + 1, sizeof(char *));
	if (new_environnement == NULL)
		return (NULL);
	i = 0;
	while (environnement[i] != NULL)
	{
		j = ft_strlen(environnement[i]);
		new_environnement[i] = ft_calloc(j + 1, sizeof(char));
		if (new_environnement[i] == NULL)
			return (NULL);
		ft_strcpy(new_environnement[i], environnement[i]);
		i += 1;
	}
	return (new_environnement);
}
