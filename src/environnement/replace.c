/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 14:58:37 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/10 11:18:29 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**replace_line_in_environnement(char **environnement, int line, char *value,
	t_list *garbage)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	while (environnement != NULL AND environnement[line][i] != EOS \
	AND environnement[line][i] != '=')
		i += 1;
	i += 1;
	new = ft_calloc(ft_strlen(value) + i, sizeof(char), garbage);
	if (new == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	ft_strncpy(new, environnement[line], i);
	j = 0;
	while (value[j] != EOS)
		new[i++] = value[j++];
	free(environnement[line]);
	environnement[line] = ft_strdup(new, garbage);
	free(new);
	if (environnement[line] == NULL)
		clean_environnement(environnement, size_of_array(environnement));
	return (environnement);
}
