/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:16:15 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/06 19:45:38 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**add_to_environnement(char **environnement, char *new)
{
	char	**new_environnement;
	char	*name;
	int		line;
	int		i;

	name = get_name_of_line(new);
	line = find_line_of_name(environnement, name);
	if (line != -1)
		return (replace_line_in_environnement(environnement, line, \
		get_value_of_line(new)));
	new_environnement = copy_environnement(environnement, 1);
	if (new_environnement == NULL)
		return (NULL);
	i = size_of_array(new_environnement);
	new_environnement[i] = ft_calloc(ft_strlen(new) + 1, sizeof(char));
	if (new_environnement[i] == NULL)
		return (NULL);
	ft_strcpy(new_environnement[i], new);
	new_environnement[i + 1] = NULL;
	free_array((void **) environnement, i);
	return (new_environnement);
}
