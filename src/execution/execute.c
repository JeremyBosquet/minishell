/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:27:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/11 19:21:59 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	execute_builtins(t_minishell *minishell, char *command, int i)
{
	if (ft_strcmp(command, "exit") == 0 AND minishell->number_of_commands == 1)
		builtins_exit(minishell, i);
	else if (ft_strcmp(command, "pwd") == 0)
		builtins_pwd(minishell, i);
	exit(0);
}

static void
	execute_command(t_minishell *minishell, int i)
{
	execve(check_path(minishell->commands[i].command[0], \
	minishell->environnement, minishell->garbage), \
	minishell->commands[i].command, minishell->environnement);
	error_exe(minishell->commands[i].command[0], NULL, "command not found", \
	errno);
}

static void
	duplicate_filedescriptor(t_minishell *minishell, int i)
{
	if (i != 0)
	{
		close(minishell->commands[i - 1].pipes[1]);
		if (dup2(minishell->commands[i - 1].pipes[0], STDIN_FILENO) == -1)
			error("dup fail1", 1);
		close(minishell->commands[i - 1].pipes[0]);
	}
	if (i != minishell->number_of_commands - 1)
	{
		close(minishell->commands[i].pipes[0]);
		if (dup2(minishell->commands[i].pipes[1], STDOUT_FILENO) == -1)
			error("dup fail2", 1);
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
	execute2(t_minishell *minishell, int i)
{
	int	j;

	j = 0;
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
	execute(t_minishell *minishell)
{
	int	i;

	minishell->pids = malloc(minishell->number_of_commands * sizeof(pid_t));
	if (minishell->pids == NULL)
		return ;
	i = 0;
	while (i < minishell->number_of_commands)
	{
		if (pipe(minishell->commands[i].pipes) == -1)
			error("pipe failed", 1);
		minishell->pids[i] = fork();
		if (minishell->pids < 0)
			error("fork fail", 1);
		else if (minishell->pids[i] == 0)
			execute2(minishell, i);
		i += 1;
	}
	i = 0;
	while (i < minishell->number_of_commands)
	{
		close(minishell->commands[i].pipes[0]);
		close(minishell->commands[i].pipes[1]);
		i += 1;
	}
	i = 0;
	while (i < minishell->number_of_commands)
		waitpid(minishell->pids[i++], NULL, 0);
	free(minishell->pids);
}

void
	execute_special_builtins(t_minishell *minishell)
{
	if (ft_strcmp(minishell->commands[0].command[0], "exit") == 0)
		builtins_exit(minishell, 0);
	else if (ft_strcmp(minishell->commands[0].command[0], "unset") == 0)
		return ;
	else if (ft_strcmp(minishell->commands[0].command[0], "export") == 0)
		return ;
	else if (ft_strcmp(minishell->commands[0].command[0], "cd") == 0)
		return ;
}
