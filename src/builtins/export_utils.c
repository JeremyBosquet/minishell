/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:47:08 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 10:07:06 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**add_oldpwd(char **environnement, t_list *garbage)
{
	char	**new_environnement;
	int		i;

	new_environnement = copy_environnement(environnement, 1, garbage);
	if (new_environnement == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	i = size_of_array(new_environnement);
	new_environnement[i] = ft_calloc(7, sizeof(char), garbage);
	if (new_environnement[i] == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	ft_strcpy(new_environnement[i], "OLDPWD");
	new_environnement[i + 1] = NULL;
	free_array((void **) environnement, i);
	return (new_environnement);
}
