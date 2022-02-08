/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:27:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 18:30:46 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	execute_builtins(t_minishell *minishell, char *command)
{
	if (ft_strcmp(command, "exit") == 0 AND minishell->number_of_commands == 1)
		builtins_exit(minishell);
	else if (ft_strcmp(command, "pwd") == 0)
		builtins_pwd(minishell);
}

static void
	execute_command(t_minishell *minishell, int i)
{
	execve(minishell->commands[i].command[0], minishell->commands[i].command, \
	minishell->environnement);
}

static void
	execute2(t_minishell *minishell)
{
	int	i;
	int	j;

	if (minishell->number_of_commands <= 0)
		return ;
	i = 0;
	while (i < minishell->number_of_commands)
	{
		j = 0;
		while (minishell->commands[i].command[j])
		{
			if (is_builtins(minishell->commands[i].command[j]) == true)
				execute_builtins(minishell, \
				minishell->commands[i].command[j]);
			else
				execute_command(minishell, i);
			j += 1;
		}
		i += 1;
	}
	exit(1);
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
		minishell->pids[i] = fork();
		if (minishell->pids < 0)
			error("fork fail", 1);
		else if (minishell->pids[i] == 0)
			execute2(minishell);
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
		builtins_exit(minishell);
	else if (ft_strcmp(minishell->commands[0].command[0], "unset") == 0)
		return ;
	else if (ft_strcmp(minishell->commands[0].command[0], "export") == 0)
		return ;
	else if (ft_strcmp(minishell->commands[0].command[0], "cd") == 0)
		return ;
}
