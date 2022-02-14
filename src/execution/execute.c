/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:27:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/14 14:21:22 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	execute_command(t_minishell *minishell, int i)
{
	execve(check_path(minishell->commands[i].command[0], \
	minishell->environnement, minishell->garbage), \
	minishell->commands[i].command, minishell->environnement);
	error_exe(minishell->commands[i].command[0], NULL, "command not found", \
	127);
}

static void
	duplicate_filedescriptor(t_minishell *minishell, int i)
{
	if (i != 0)
	{
		close(minishell->commands[i - 1].pipes[1]);
		if (dup2(minishell->commands[i - 1].pipes[0], STDIN_FILENO) == -1)
			error("dup fail", 1);
		close(minishell->commands[i - 1].pipes[0]);
	}
	if (i != minishell->number_of_commands - 1)
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

/*
 * For pwd command, get current directory without variable in environnement
 * For pipes, use command[i - 1]
 */
static void
	execute(t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	signal(SIGINT, NULL);
	closefd(minishell, i);
	duplicate_filedescriptor(minishell, i);
	while (minishell->commands[i].command[j])
	{
		if (is_builtins(minishell->commands[i].command[j]) == true)
			execute_builtins(minishell, \
			minishell->commands[i].command[j], i);
		else
			execute_command(minishell, i);
		j += 1;
	}
}

void
	child(t_minishell *minishell)
{
	int	i;

	minishell->pids = malloc(minishell->number_of_commands * sizeof(pid_t));
	if (minishell->pids == NULL)
		return ;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (i < minishell->number_of_commands)
	{
		if (pipe(minishell->commands[i].pipes) == -1)
			error("pipe fail", 1);
		minishell->pids[i] = fork();
		if (minishell->pids < 0)
			error("fork fail", 1);
		else if (minishell->pids[i] == 0)
			execute(minishell, i);
		i += 1;
	}
	closefd(minishell, i);
	i = 0;
	while (i < minishell->number_of_commands)
		waitpid(minishell->pids[i++], &minishell->exit_code, WUNTRACED);
	signal(SIGINT, handle_signals);
	minishell->exit_code /= 256;
	free(minishell->pids);
}
