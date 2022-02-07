/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:15:41 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/07 20:28:22 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	free_parse(char ***commands_splitted, char **line_commands, int i1, int i2)
{
	int	i;

	i = 0;
	if (i1 != 0)
	{
		while (i < i1)
		{
			free_array((void *)commands_splitted[i], size_of_array(commands_splitted[i]));
			i++;
		}
		free(commands_splitted);
	}
	if (i2 != 0)
		free_array((void *)line_commands, i2);
	error("out of memory", EXIT_FAILURE);
}

static int	size_of_3array(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_dup_2array(char **src)
{
	int		i;
	char	**dest;

	i = 0;
	dest = ft_calloc(sizeof(char *), size_of_array(src) + 1);
	if (src == NULL)
		return (NULL); //FREE dest
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		free(src[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	free(src);
	return (dest);
}

void	fill_struct(t_minishell *minishell, char ***cmds)
{
	int	i;

	i = 0;
	minishell->commands = ft_calloc(sizeof(t_command), size_of_3array(cmds) + 1);
	if (!minishell->commands)
		return ;
	minishell->number_of_commands = size_of_3array(cmds);
	while (cmds[i])
	{
		minishell->commands[i].command = ft_dup_2array(cmds[i]);
		i += 1;
	}
}

void	
	parse_new_line(t_minishell *minishell, char *new_line)
{
	int		i;
	char	**line_cmds;
	char	***cmds_split;

	i = 0;
	// CHECK QUOTES NON FERME OU PIPE A LA FIN OU DEUX D'AFFILER
	line_cmds = ft_split_with_quotes(new_line, '|');
	if (!line_cmds)
		return ;
	cmds_split = ft_calloc(sizeof(char **), size_of_array(line_cmds) + 1);
	if (cmds_split == NULL)
		free_parse(cmds_split, line_cmds, 0, size_of_array(line_cmds));
	while (line_cmds[i])
	{
		cmds_split[i] = ft_split_with_quotes(line_cmds[i], ' ');
		if (cmds_split[i] == NULL)
			free_parse(cmds_split, line_cmds, size_of_array(cmds_split[i]), i);
		free(line_cmds[i]);
		i++;
	}
	free(line_cmds);
	cmds_split[i] = 0;
	// FONCTIONS POUR PARSER ET REGARDER LE TRIPLE TABLEAU
	fill_struct(minishell, cmds_split);
}
