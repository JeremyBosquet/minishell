/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:47:08 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 15:04:04 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**delete_line_in_export(char **environnement, char *name, t_list *g)
{
	int		i;
	int		j;
	int		size;
	char	**new_environnement;

	size = size_of_array(environnement);
	new_environnement = ft_calloc(size + 1, sizeof(char *), g);
	if (new_environnement == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (environnement[i] != NULL)
	{
		if (i == find_line_of_name2(environnement, name) AND i != size)
			i += 1;
		else
			new_environnement[j++] = ft_strdup(environnement[i++], g);
	}
	free_array((void **) environnement, size);
	return (new_environnement);
}

char
	**add_to_export(char **environnement, char *command, t_list *garbage)
{
	char	**new;
	int		i;
	int		line;
	char	*name;

	if (ft_strchr(command, '=') != NULL)
	{
		name = get_name_of_line(command, garbage);
		if (find_line_of_name2(environnement, name) != -1)
			environnement = delete_line_in_export(environnement, name, garbage);
		free(name);
	}
	line = find_line_of_name2(environnement, command);
	if (line != -1)
		return (environnement);
	new = copy_environnement(environnement, 1, garbage);
	if (new == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	i = size_of_array(new);
	new[i] = ft_calloc(ft_strlen(command) + 1, sizeof(char), garbage);
	if (new[i] == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	ft_strcpy(new[i], command);
	free_array((void **) environnement, i);
	return (new);
}
