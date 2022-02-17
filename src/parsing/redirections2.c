/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 21:40:24 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 09:26:38 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	**clean_redirection(t_minishell *minishell, int i, int *j)
{
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	minishell->commands[i].command = remove_line_2array(\
	minishell->commands[i].command, *j, \
	size_of_array(minishell->commands[i].command), minishell->garbage);
	return (minishell->commands[i].command);
}

static char
	*child_here_doc(t_minishell *minishell, int i, int *j, char *new_line)
{
	char	*final;

	final = NULL;
	while (ft_strcmp(new_line, minishell->commands[i].command[*j + 1]) != 0)
	{
		new_line = readline("> ");
		if (!new_line)
		{
			printf("\033[1A\033[2C");
			break ;
		}
		if (!ft_strcmp(new_line, minishell->commands[i].command[*j + 1]))
		{
			if (*new_line)
				free(new_line);
			break ;
		}
		new_line = ft_strfjoin(new_line, "\n", 1, minishell->garbage);
		if (!final)
			final = ft_strdup("", minishell->garbage);
		final = ft_strfjoin(final, new_line, 3, minishell->garbage);
		if (final == NULL)
			return (NULL);
	}
	return (final);
}

static void
	wait_here_doc(t_minishell *minishell, pid_t child, int i)
{
	int	status;

	waitpid(child, &status, WUNTRACED);
	if (WIFEXITED(status))
		g_exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		minishell->commands[i].do_run = false;
	signal(SIGINT, handle_signals);
}

static void
	child1(t_minishell *minishell, int i, int *j, char *new_line)
{
	char	*final;

	signal(SIGINT, signal_child);
	final = child_here_doc(minishell, i, j, new_line);
	new_line = ft_strdup(".couscous_cmd_", minishell->garbage);
	new_line = ft_strfjoin(new_line, ft_itoa(i), 3, minishell->garbage);
	minishell->commands[i].fd_in = open(new_line, O_RDWR | O_TRUNC \
	| O_CREAT, 0644);
	write(minishell->commands[i].fd_in, final, ft_strlen(final));
	close(minishell->commands[i].fd_in);
	free(new_line);
	free(final);
	exit(0);
}

char
	**redir_hered(t_minishell *minishell, int i, int *j)
{
	char	*new_line;
	pid_t	child_heredoc;

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
			child1(minishell, i, j, new_line);
		wait_here_doc(minishell, child_heredoc, i);
		new_line = ft_strdup(".couscous_cmd_", minishell->garbage);
		minishell->commands[i].file_in = ft_strfjoin(new_line, ft_itoa(i), 3, \
		minishell->garbage);
	}
	minishell->commands[i].command = clean_redirection(minishell, i, j);
	return (minishell->commands[i].command);
}
