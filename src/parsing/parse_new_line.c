/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:15:41 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/14 20:21:06 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell2.h"

static int	size_of_3array(char ***str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**ft_dup_2array(char **src, t_list *garbage, int opt)
{
	int		i;
	char	**dest;

	i = 0;
	dest = ft_calloc(sizeof(char *), size_of_array(src) + 1, \
	garbage);
	if (src == NULL)
	{
		free(dest);
		return (NULL);
	}
	while (src[i])
	{
		dest[i] = ft_strdup(src[i], garbage);
		if (opt == 1)
			free(src[i]);
		if (!dest[i])
			return (NULL);
		i++;
	}
	if (opt == 1)
		free(src);
	return (dest);
}

static void
	fill_struct(t_minishell *minishell, char ***cmds, t_list *garbage)
{
	int	i;

	i = 0;
	minishell->commands = ft_calloc(sizeof(t_command), \
	size_of_3array(cmds) + 1, garbage);
	if (!minishell->commands)
		return ;
	minishell->number_of_commands = size_of_3array(cmds);
	while (cmds[i])
	{
		minishell->commands[i].command = ft_dup_2array(cmds[i], garbage, 1);
		i += 1;
	}
	free(cmds);
}

void
	parse_new_line(t_minishell *minishell, char *new_line)
{
	int		i;
	char	**line_cmds;
	char	***cmds_split;

	i = 0;
	new_line = check_new_line(new_line, minishell->garbage);
	if (new_line == NULL)
	{
		minishell->exit_code = 258;
		return ;
	}
	line_cmds = ft_split_with_quotes(new_line, '|', minishell->garbage);
	if (!line_cmds)
		return ;
	cmds_split = ft_calloc(sizeof(char **), size_of_array(line_cmds) + 1, minishell->garbage);
	// if (cmds_split == NULL)
		// free_parse(cmds_split, line_cmds, 0, size_of_array(line_cmds));
	replace_env(line_cmds, minishell);
	while (line_cmds[i])
	{
		cmds_split[i] = ft_split_with_quotes(line_cmds[i], ' ', minishell->garbage);
		// if (cmds_split[i] == NULL)
			// free_parse(cmds_split, line_cmds, size_of_array(cmds_split[i]), i);
		free(line_cmds[i]);
		i++;
	}
	free(line_cmds);
	replace_quotes(cmds_split, minishell);
	fill_struct(minishell, cmds_split, minishell->garbage);
	free(new_line);
	//PARSING DES REDIRECTIONS
	print_commands(minishell);
}
