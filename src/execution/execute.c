/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:27:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/15 13:59:15 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

//static void
//	duplicate_redirection(t_minishell *minishell, int i, int type)
//{
//	if (type == 0)
//	{
//		if (dup2(minishell->commands[i].filedescriptor_in, STDIN_FILENO) == -1)
//			error("dup fail", 1);
//		close(minishell->commands[i].filedescriptor_in);
//	}
//	else if (type == 1)
//	{
//		if (dup2(minishell->commands[i].filedescriptor_out, \
//		STDOUT_FILENO) == -1)
//			error("dup fail", 1);
//		close(minishell->commands[i].filedescriptor_out);
//	}
//}

static void
	duplicate_filedescriptor(t_minishell *minishell, int i)
{
//	if (minishell->commands[i].filedescriptor_in != 0)
//		duplicate_redirection(minishell, i, 0);
	if (i != 0)
	{
		close(minishell->commands[i - 1].pipes[1]);
		if (dup2(minishell->commands[i - 1].pipes[0], STDIN_FILENO) == -1)
			error("dup fail", 1);
		close(minishell->commands[i - 1].pipes[0]);
	}
//	if (minishell->commands[i].filedescriptor_out != 1)
//		duplicate_redirection(minishell, i, 1);
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

static void
	child(t_minishell *minishell, int i)
{
	int	j;

	j = 0;
	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
	closefd(minishell, i);
	duplicate_filedescriptor(minishell, i);
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
		if (is_builtins(minishell->commands[i].command[j]) == true)
			execute_builtins(minishell, \
			minishell->commands[i].command[j], i);
		else
		{
			execve(check_path(minishell->commands[i].command[0], \
			minishell->environnement, minishell->garbage), \
			minishell->commands[i].command, minishell->environnement);
			error_exe(minishell->commands[i].command[0], NULL, \
			"command not found", 127);
		}
		j += 1;
	}
}

void
	execute(t_minishell *minishell)
{
	int		i;
	int		status;
	bool	are_signal;

	minishell->pids = malloc(minishell->number_of_commands * sizeof(pid_t));
	if (minishell->pids == NULL)
		return ;
	are_signal = false;
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
	i = 0;
	while (i < minishell->number_of_commands)
	{
		waitpid(minishell->pids[i++], &status, WUNTRACED);
		if (WIFEXITED(status))
			g_exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && are_signal == false)
		{
			signal_child(WTERMSIG(status));
			are_signal = true;
		}
	}
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	free(minishell->pids);
}
