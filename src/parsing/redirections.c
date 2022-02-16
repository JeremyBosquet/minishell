/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 17:25:06 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 20:00:55 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell2.h"

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
	minishell->commands[i].command[*j + 1] = \
	replace_values_quotes(minishell->commands[i].command[*j + 1], minishell);
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
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	if (minishell->commands[i].fd_out > 2)
		close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}

char
	**redir_append_out(t_minishell *minishell, int i, int *j)
{
	minishell->commands[i].type_outfile = APPEND;
	minishell->commands[i].command[*j + 1] = \
	replace_values_quotes(minishell->commands[i].command[*j + 1], minishell);
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
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	if (minishell->commands[i].fd_out > 2)
		close(minishell->commands[i].fd_out);
	return (minishell->commands[i].command);
}

char
	**redir_simple_in(t_minishell *minishell, int i, int *j)
{
	minishell->commands[i].type_infile = SIMPLE;
	minishell->commands[i].command[*j + 1] = \
	replace_values_quotes(minishell->commands[i].command[*j + 1], minishell);
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
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, \
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
	int		status;
	pid_t	child_heredoc;

	final = NULL;
	new_line = NULL;
	minishell->commands[i].type_infile = HEREDOC;
	minishell->commands[i].command[*j + 1] = \
	replace_values_quotes(minishell->commands[i].command[*j + 1], minishell);
	if (minishell->commands[i].do_open_in)
	{
		signal(SIGINT, SIG_IGN);
		child_heredoc = fork();
		if (child_heredoc < 0)
			error("fork fail", 1);
		else if (child_heredoc == 0)
		{
			signal(SIGINT, signal_heredoc);
			while (ft_strcmp(new_line, minishell->commands[i].command[*j + 1]) != 0)
			{
				new_line = readline("> ");
				if (!new_line)
				{
					printf("\033[1A\033[2C");
					break ;
				}
				if (ft_strcmp(new_line, minishell->commands[i].command[*j + 1]) == 0)
				{
					if (*new_line)
						free(new_line);
					break ;
				}
				new_line = ft_strfjoin(new_line, "\n", 1, minishell->garbage);
				if (!final)
					final = ft_strdup("", minishell->garbage);
				final = ft_strfjoin(final, new_line, 3, minishell->garbage);
			}
			new_line = ft_strdup(".couscous_cmd_", minishell->garbage);
			new_line = ft_strfjoin(new_line, ft_itoa(i), 3, minishell->garbage);
			minishell->commands[i].fd_in = open(new_line, O_RDWR | O_TRUNC | O_CREAT, 0644);
			write(minishell->commands[i].fd_in, final, ft_strlen(final));
			close(minishell->commands[i].fd_in);
			exit(0);
		}
		waitpid(child_heredoc, &status, WUNTRACED);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			minishell->commands[i].do_run = false;
		signal(SIGINT, handle_signals);
		new_line = ft_strdup(".couscous_cmd_", minishell->garbage);
		minishell->commands[i].file_in = ft_strfjoin(new_line, ft_itoa(i), 3, minishell->garbage);
	}
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, size_of_array(minishell->commands[i].command), minishell->garbage);
	return (minishell->commands[i].command);
}

void
	redirections(t_minishell *minishell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < minishell->number_of_commands)
	{
		j = 0;
		minishell->commands[i].fd_in = STDIN;
		minishell->commands[i].fd_out = STDOUT;
		minishell->commands[i].do_open_in = true;
		minishell->commands[i].do_open_out = true;
		minishell->commands[i].file_in = NULL;
		minishell->commands[i].file_out = NULL;
		minishell->commands[i].do_run = true;
		while (minishell->commands[i].command[j])
		{
			if (ft_strcmp(minishell->commands[i].command[j], ">") == 0)
				minishell->commands[i].command = redir_simple_out(minishell, i, &j);
			else if (ft_strcmp(minishell->commands[i].command[j], ">>") == 0)
				minishell->commands[i].command = redir_append_out(minishell, i, &j);
			else if (ft_strcmp(minishell->commands[i].command[j], "<") == 0)
				minishell->commands[i].command = redir_simple_in(minishell, i, &j);
			else if (ft_strcmp(minishell->commands[i].command[j], "<<") == 0)
				minishell->commands[i].command = redir_heredoc(minishell, i, &j);
			else
			{
				minishell->commands[i].command[j] = \
				replace_values_quotes(minishell->commands[i].command[j], \
				minishell);
				j++;
			}
		}
	}
}
