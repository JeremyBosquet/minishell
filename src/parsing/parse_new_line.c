/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:15:41 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/09 11:26:04 by jbosquet         ###   ########.fr       */
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
			free_array((void *)commands_splitted[i], \
			size_of_array(commands_splitted[i]));
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
	{
		free(dest);
		return (NULL);
	}
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
	minishell->commands = ft_calloc(sizeof(t_command), \
	size_of_3array(cmds) + 1);
	if (!minishell->commands)
		return ;
	minishell->number_of_commands = size_of_3array(cmds);
	while (cmds[i])
	{
		minishell->commands[i].command = ft_dup_2array(cmds[i]);
		i += 1;
	}
	idebug(minishell->number_of_commands);
}

/*
 * Vérifier que les quotes et les pipes soit bien fermés, ou s'il y a deux pipes
 * à la suite.
 * Parser le triple tableau.
 * Regarder le triple tableau.
*/

static int
	check_quotes(char *new_line)
{
	int	i;
	int	simple_quotes;
	int	double_quotes;	

	i = 0;
	simple_quotes = 1;
	double_quotes = 1;
	while (new_line[i])
	{
		if (new_line[i] == '\'')
		{
			simple_quotes = -simple_quotes;
			i += return_value_after_quote(new_line, i);
			if (new_line[i - 1] == '\'')
				simple_quotes = -simple_quotes;
			if (i >= ft_strlen(new_line))
				break ;
		}
		else if (new_line[i] == '"')
		{
			double_quotes = -double_quotes;
			i += return_value_after_quote(new_line, i);
			if (new_line[i - 1] == '"')
				double_quotes = -double_quotes;
			if (i >= ft_strlen(new_line))
				break ;
		}
		else
			i++;
	}
	if (simple_quotes != 1 OR double_quotes != 1)
	{
		printf("couscous-0.1: syntax error on quotes\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int
	check_pipe(char *new_line)
{
	int	i;
	int	only_space_before_pipe;

	i = 0;
	only_space_before_pipe = 1;
	while (new_line[i])
	{
		if (new_line[i] != '|' && new_line[i] != ' ')
			only_space_before_pipe = -1;
		if (new_line[i] == '|')
		{
			if (only_space_before_pipe == 1)
			{
				printf("couscous-0.1: syntax error near unexpected token `|'\n");
				return (EXIT_FAILURE);
			}
			else
				only_space_before_pipe = 1;
		}
		i++;
	}
	if (only_space_before_pipe == 1)
		return (2);
	return (EXIT_SUCCESS);
}

static char *
	check_new_line(char *new_line)
{
	char	*heredoc;

	if (ft_strlen(new_line) == 0)
		return (NULL);
	if (check_pipe(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_quotes(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_pipe(new_line) == 2)
	{
		heredoc = readline("> ");
		if (heredoc == NULL)
		{
			printf("couscous-0.1: syntax error: unexpected end of file\n");
			return (NULL);
		}
		new_line = ft_strjoin(new_line, heredoc);
		// free(heredoc);
		new_line = check_new_line(new_line);
	}
	return (new_line);
}

void
	parse_new_line(t_minishell *minishell, char *new_line)
{
	int		i;
	char	**line_cmds;
	char	***cmds_split;

	i = 0;
	new_line = check_new_line(new_line);
	if (new_line == NULL)
		return ;
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
	fill_struct(minishell, cmds_split);
}
