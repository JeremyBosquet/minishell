/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:15:41 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/07 18:07:01 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	
	parse_new_line(char *new_line)
{
	int		i;
	int		j;
	char	**line_commands;
	char	***commands_splitted;

	i = 0;
	// CHECK QUOTES NON FERME OU PIPE A LA FIN OU DEUX D'AFFILER
	line_commands = ft_split_with_quotes(new_line, '|');
	if (!line_commands)
		return (EXIT_FAILURE);
	commands_splitted = ft_calloc(sizeof(char **), size_of_array(line_commands) + 1);
	if (commands_splitted == NULL)
		return (EXIT_FAILURE);
	while (line_commands[i])
	{
		commands_splitted[i] = ft_split_with_quotes(line_commands[i], ' ');
		free(line_commands[i]);
		if (!commands_splitted[i])
			return (EXIT_FAILURE);
		i++;
	}
	free(line_commands);
	commands_splitted[i] = 0;
	i = 0;
	while (commands_splitted[i])
	{
		j = 0;
		printf("=======\n");
		while (commands_splitted[i][j])
			j++;
		i++;
	}
	// FONCTIONS POUR PARSER ET REGARDER LE TRIPLE TABLEAU ET METTRE TOUTES LES INFOS 
	return (EXIT_SUCCESS);
}
