/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:15:41 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/18 18:34:48 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char
	***parse_new_line2(t_minishell *minishell, char **line_cmds)
{
	int		i;
	char	***cmds_split;

	i = 0;
	cmds_split = ft_calloc(sizeof(char **), size_of_array(line_cmds) + 1, \
	minishell->garbage);
	if (cmds_split == NULL)
		return (NULL);
	while (line_cmds[i])
	{
		cmds_split[i] = ft_split_with_quotes(line_cmds[i], ' ', \
		minishell->garbage);
		if (cmds_split[i] == NULL)
			return (NULL);
		free(line_cmds[i]);
		i += 1;
	}
	free(line_cmds);
	return (cmds_split);
}

void
	parse_new_line(t_minishell *minishell, char *new_line)
{
	char	**line_cmds;
	char	***cmds_split;
	int		j;
	char	*line;

	j = 0;
	line = ft_strdup(new_line, minishell->garbage);
	line = check_new_line(line, minishell->garbage);
	if (line == NULL)
	{
		g_exit_code = 258;
		return ;
	}
	line_cmds = ft_split_with_quotes(line, '|', minishell->garbage);
	if (!line_cmds)
		return ;
	replace_env(line_cmds, minishell);
	cmds_split = parse_new_line2(minishell, line_cmds);
	if (cmds_split == NULL)
		return ((void)free_array((void **) line_cmds, \
		size_of_array(line_cmds)));
	fill_struct(minishell, cmds_split, minishell->garbage);
	free(line);
	redirections(minishell, j);
}
