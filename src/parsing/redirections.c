/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:25:06 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/17 15:40:36 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**remove_line_2array(char **tabs, int line, int size, t_list *g)
{
	int		i;
	int		j;
	char	**new_tab;

	new_tab = ft_calloc(size, sizeof(char *), g);
	if (new_tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tabs[i] != NULL)
	{
		if (i == line AND i != size)
			i += 1;
		else
			new_tab[j++] = ft_strdup(tabs[i++], g);
	}
	free_array((void **) tabs, size);
	return (new_tab);
}

char
	**redir_s_out(t_minishell *minishell, int i, int j)
{
	minishell->commands[i].type_outfile = TRUNC;
	minishell->commands[i].command[j + 1] = \
	replace_values_quotes(minishell->commands[i].command[j + 1], minishell);
	if (minishell->commands[i].do_open_out && minishell->commands[i].do_open_in)
	{
		minishell->commands[i].fd_out = \
		open(minishell->commands[i].command[j + 1], \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (minishell->commands[i].fd_out == -1)
			minishell->commands[i].do_open_out = false;
		minishell->commands[i].file_out = \
		ft_strdup(minishell->commands[i].command[j + 1], minishell->garbage);
	}
	minishell->commands[i].command = clean_redirection(minishell, i, &j);
	if (minishell->commands[i].fd_out > 2)
		close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}

char
	**redir_a_out(t_minishell *minishell, int i, int j)
{
	minishell->commands[i].type_outfile = APPEND;
	minishell->commands[i].command[j + 1] = \
	replace_values_quotes(minishell->commands[i].command[j + 1], minishell);
	if (minishell->commands[i].do_open_out && minishell->commands[i].do_open_in)
	{
		minishell->commands[i].fd_out = \
		open(minishell->commands[i].command[j + 1], \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (minishell->commands[i].fd_out == -1)
			minishell->commands[i].do_open_out = false;
		minishell->commands[i].file_out = \
		ft_strdup(minishell->commands[i].command[j + 1], minishell->garbage);
	}
	minishell->commands[i].command = clean_redirection(minishell, i, &j);
	if (minishell->commands[i].fd_out > 2)
		close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}

char
	**redir_s_in(t_minishell *minishell, int i, int j)
{
	minishell->commands[i].type_infile = SIMPLE;
	minishell->commands[i].command[j + 1] = \
	replace_values_quotes(minishell->commands[i].command[j + 1], minishell);
	if (minishell->commands[i].do_open_in)
	{
		minishell->commands[i].fd_in = \
		open(minishell->commands[i].command[j + 1], O_RDONLY);
		if (minishell->commands[i].fd_in == -1)
			minishell->commands[i].do_open_in = false;
		minishell->commands[i].file_in = \
		ft_strdup(minishell->commands[i].command[j + 1], minishell->garbage);
	}
	minishell->commands[i].command = clean_redirection(minishell, i, &j);
	if (minishell->commands[i].fd_in > 2)
		close(minishell->commands[i].fd_in);
	return (minishell->commands[i].command);
}

void
	redirections(t_minishell *minishell, int j)
{
	int	i;

	i = -1;
	while (++i < minishell->number_of_commands)
	{
		init_fd_command(minishell, i);
		j = 0;
		while (minishell->commands[i].command[j])
		{
			if (ft_strcmp(minishell->commands[i].command[j], ">") == 0)
				minishell->commands[i].command = redir_s_out(minishell, i, j);
			else if (ft_strcmp(minishell->commands[i].command[j], ">>") == 0)
				minishell->commands[i].command = redir_a_out(minishell, i, j);
			else if (ft_strcmp(minishell->commands[i].command[j], "<") == 0)
				minishell->commands[i].command = redir_s_in(minishell, i, j);
			else if (ft_strcmp(minishell->commands[i].command[j], "<<") == 0)
				minishell->commands[i].command = redir_hered(minishell, i, j);
			else
			{
				minishell->commands[i].command[j] = replace_values_quotes(\
				minishell->commands[i].command[j], minishell);
				j++;
			}
		}
	}
}
