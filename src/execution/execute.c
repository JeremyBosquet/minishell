/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:27:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/18 10:26:53 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	duplicate_redirection(t_minishell *minishell, int i, int type, int type2)
{
	if (type == 0)
	{
		minishell->commands[i].fd_in = open(\
		minishell->commands[i].file_in, O_RDONLY);
		if (minishell->commands[i].fd_in == -1)
			return ;
		if (dup2(minishell->commands[i].fd_in, STDIN_FILENO) == -1)
			error("dup fail", 1);
		close(minishell->commands[i].fd_in);
	}
	else if (type == 1)
	{
		if (type2 == TRUNC)
			minishell->commands[i].fd_out = open(\
			minishell->commands[i].file_out, O_WRONLY | O_TRUNC);
		else if (type2 == APPEND)
			minishell->commands[i].fd_out = open(\
			minishell->commands[i].file_out, O_WRONLY | O_APPEND);
		if (minishell->commands[i].fd_out == -1)
			return ;
		if (dup2(minishell->commands[i].fd_out, \
		STDOUT_FILENO) == -1)
			error("dup fail", 1);
		close(minishell->commands[i].fd_out);
	}
}

static void
	duplicate_filedescriptor(t_minishell *minishell, int i)
{
	if (minishell->commands[i].do_open_in == false)
		error_exe(minishell->commands[i].file_in, NULL, \
		"No such file or directory", 1);
	if (minishell->commands[i].file_in != NULL)
		duplicate_redirection(minishell, i, 0, \
		minishell->commands[i].type_infile);
	else if (i != 0)
	{
		close(minishell->commands[i - 1].pipes[1]);
		if (dup2(minishell->commands[i - 1].pipes[0], STDIN_FILENO) == -1)
			error("dup fail", 1);
		close(minishell->commands[i - 1].pipes[0]);
	}
	if (minishell->commands[i].do_open_out == false)
		error_exe(minishell->commands[i].file_out, NULL, PDENIED, 1);
	if (minishell->commands[i].file_out != NULL)
		duplicate_redirection(minishell, i, 1, \
		minishell->commands[i].type_outfile);
	else if (i != minishell->number_of_commands - 1)
	{
		close(minishell->commands[i].pipes[0]);
		if (dup2(minishell->commands[i].pipes[1], STDOUT_FILENO) == -1)
			error("dup fail", 1);
		close(minishell->commands[i].pipes[1]);
	}
}

static void
	closefd(t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	while (j < i - 1)
	{
		close(minishell->commands[j].pipes[0]);
		close(minishell->commands[j].pipes[1]);
		j += 1;
	}
}

static void
	child(t_minishell *minishell, int i)
{
	int		j;

	j = 0;
	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	closefd(minishell, i);
	duplicate_filedescriptor(minishell, i);
	if ((minishell->commands[i].command[0] == NULL \
	OR minishell->commands[i].do_run == false) \
	AND minishell->commands[i].type_infile == HEREDOC)
		exit(g_exit_code);
	if (minishell->commands[i].command[0] == NULL)
	{
		j += 1;
		execve(minishell->commands[i].command[0], \
		minishell->commands[i].command, minishell->environnement);
		error_exe(minishell->commands[i].command[0], NULL, \
		"command not found", 127);
	}
	while (minishell->commands[i].command[j])
	{
		child_loop(minishell, i, j);
		j += 1;
	}
}

void
	execute(t_minishell *minishell)
{
	int		i;

	minishell->pids = malloc(minishell->number_of_commands * sizeof(pid_t));
	if (minishell->pids == NULL)
		return ;
	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while (i < minishell->number_of_commands)
	{
		if (pipe(minishell->commands[i].pipes) == -1)
			error("pipe fail", 1);
		minishell->pids[i] = fork();
		if (minishell->pids < 0)
			error("fork fail", 1);
		else if (minishell->pids[i] == 0)
			child(minishell, i);
		i += 1;
	}
	closefd(minishell, i + 1);
	wait_exec(minishell);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	free(minishell->pids);
}
