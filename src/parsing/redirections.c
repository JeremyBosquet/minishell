/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:25:06 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/15 23:17:13 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//CRASH QUAND AUCUNE COMMANDE
//CRASH QUAND LA COMMANDE EST APRES

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
	**redir_simple_out(t_minishell *minishell, int i, int *j)
{
	minishell->commands[i].type_outfile = TRUNC;
	if (minishell->commands[i].do_open_out && minishell->commands[i].do_open_in)
	{
		minishell->commands[i].fd_out = \
		open(minishell->commands[i].command[*j + 1], \
		O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (minishell->commands[i].fd_out == -1)
			minishell->commands[i].do_open_out = false;
		minishell->commands[i].file_out = \
		ft_strdup(minishell->commands[i].command[*j + 1], minishell->garbage);
	}
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j,\
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j,\
	size_of_array(minishell->commands[i].command), minishell->garbage);
	if (minishell->commands[i].fd_out > 2)
		close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}

char
	**redir_append_out(t_minishell *minishell, int i, int *j)
{
	minishell->commands[i].type_outfile = APPEND;
	if (minishell->commands[i].do_open_out && minishell->commands[i].do_open_in)
	{
		minishell->commands[i].fd_out = \
		open(minishell->commands[i].command[*j + 1], \
		O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (minishell->commands[i].fd_out == -1)
			minishell->commands[i].do_open_out = false;
		minishell->commands[i].file_out = \
		ft_strdup(minishell->commands[i].command[*j + 1], minishell->garbage);
	}
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j,\
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j,\
	size_of_array(minishell->commands[i].command), minishell->garbage);
	if (minishell->commands[i].fd_out > 2)
		close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}


char
	**redir_simple_in(t_minishell *minishell, int i, int *j)
{
	minishell->commands[i].type_infile = SIMPLE;
	if (minishell->commands[i].do_open_in)
	{
		minishell->commands[i].fd_in = \
		open(minishell->commands[i].command[*j + 1], O_RDONLY);
		if (minishell->commands[i].fd_in == -1)
			minishell->commands[i].do_open_in = false;
		minishell->commands[i].file_in = \
		ft_strdup(minishell->commands[i].command[*j + 1], minishell->garbage);
	}
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j,\
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j,\
	size_of_array(minishell->commands[i].command), minishell->garbage);
	if (minishell->commands[i].fd_in > 2)
		close(minishell->commands[i].fd_in);
	return (minishell->commands[i].command);
}

char
	**redir_heredoc(t_minishell *minishell, int i, int *j)
{
	char	*final;
	char	*new_line;

	final = NULL;
	new_line = NULL;
	minishell->commands[i].type_outfile = HEREDOC;
	if (minishell->commands[i].do_open_out)
	{
		while (ft_strcmp(new_line, minishell->commands[i].command[*j + 1]) != 0)
		{
			new_line = readline("> ");
			if (!new_line)
				break ;
			if (ft_strcmp(new_line, minishell->commands[i].command[*j + 1]) == 0)
			{
				if (*new_line)
					free(new_line);
				break ;
			}
			new_line = ft_strfjoin(new_line, "\n", 1, minishell->garbage);
			if (!final)
				final = ft_strdup("", minishell->garbage);
			//calculer la taille de new_line + final et voir si elle est superieur a 65000...
			final = ft_strfjoin(final, new_line, 3, minishell->garbage);
		}
		new_line = ft_strdup(".couscous_cmd_", minishell->garbage);
		new_line = ft_strfjoin(new_line, ft_itoa(i), 3, minishell->garbage);
		minishell->commands[i].fd_out = open(new_line, O_RDWR | O_TRUNC | O_CREAT, 0644);
		write(minishell->commands[i].fd_out, final, ft_strlen(final));
		close(minishell->commands[i].fd_out);
		minishell->commands[i].file_out = ft_strdup(new_line, minishell->garbage);
	}
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, size_of_array(minishell->commands[i].command), minishell->garbage);
	// if (minishell->commands[i].fd_out > 2)
	// 	close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}

void
	redirections(t_minishell *minishell)
{
	int i;
	int j;

	i = 0;
	while (i < minishell->number_of_commands)
	{
		j = 0;
		minishell->commands[i].fd_in = STDIN;
		minishell->commands[i].fd_out = STDOUT;
		minishell->commands[i].do_open_in = true;
		minishell->commands[i].do_open_out = true;
		while (minishell->commands[i].command[j])
		{
			if (ft_strcmp( minishell->commands[i].command[j], ">") == 0)
				minishell->commands[i].command = redir_simple_out(minishell, i, &j);
			else if (ft_strcmp(minishell->commands[i].command[j], ">>") == 0)
			    minishell->commands[i].command = redir_append_out(minishell, i, &j);
			else if (ft_strcmp(minishell->commands[i].command[j], "<") == 0)
			    minishell->commands[i].command = redir_simple_in(minishell, i, &j);
			else if (ft_strcmp(minishell->commands[i].command[j], "<<") == 0)
			    minishell->commands[i].command = redir_heredoc(minishell, i, &j);
			else
				j++;
		}    
		i++;
	}
}
