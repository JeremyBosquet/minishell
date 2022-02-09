/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:16:15 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/09 18:23:52 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**add_to_environnement(char **environnement, char *new, t_list *garbage)
{
	char	**new_environnement;
	char	*name;
	int		line;
	int		i;

	name = get_name_of_line(new, garbage);
	line = find_line_of_name(environnement, name, garbage);
	if (line != -1)
	{
		free(name);
		return (replace_line_in_environnement(environnement, line, \
		get_value_of_line(new, garbage), garbage));
	}
	new_environnement = copy_environnement(environnement, 1, garbage);
	if (new_environnement == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	i = size_of_array(new_environnement);
	new_environnement[i] = ft_calloc(ft_strlen(new) + 1, sizeof(char), \
	garbage);
	if (new_environnement[i] == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	ft_strcpy(new_environnement[i], new);
	new_environnement[i + 1] = NULL;
	free_array((void **) environnement, i);
	return (new_environnement);
}
