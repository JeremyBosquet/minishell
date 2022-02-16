/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:50:17 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/16 17:31:06 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	check_directory(t_minishell *minishell, int i)
{
	int	fd;

	fd = open(minishell->commands[i].command[0], O_DIRECTORY);
	if (fd > 0)
	{
		close(fd);
		error_exe(minishell->commands[i].command[0], NULL, \
		"is a directory", 126);
	}
}

void
	child_loop(t_minishell *minishell, int i, int j)
{
	int	fd;

	if (is_builtins(minishell->commands[i].command[j]) == true)
		execute_builtins(minishell, minishell->commands[i].command[j], i);
	else
	{
		check_directory(minishell, i);
		fd = open(check_path(minishell->commands[i].command[0], \
		minishell->environnement, minishell->garbage), O_RDONLY);
		if (fd < 0)
		{
			close(fd);
			error_exe(minishell->commands[i].command[0], NULL, \
			"command not found", 127);
		}
		if (access(check_path(minishell->commands[i].command[0], \
		minishell->environnement, minishell->garbage), X_OK) != 0)
			error_exe(minishell->commands[i].command[0], NULL, \
			"permission1 denied", 126);
		execve(check_path(minishell->commands[i].command[0], \
		minishell->environnement, minishell->garbage), \
		minishell->commands[i].command, minishell->environnement);
	}
}

void
	wait_exec(t_minishell *minishell)
{
	int		i;
	int		status;
	bool	are_signal;

	i = 0;
	are_signal = false;
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
}
