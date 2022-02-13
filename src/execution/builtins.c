/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:32:32 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/13 11:43:37 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

bool
	is_builtins(char *command)
{
	if (ft_strcmp(command, "echo") == 0 OR ft_strcmp(command, "cd") == 0 \
	OR ft_strcmp(command, "pwd") == 0 OR ft_strcmp(command, "export") == 0 \
	OR ft_strcmp(command, "unset") == 0 OR ft_strcmp(command, "env") == 0 \
	OR ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}

bool
	is_special_builtins(char *command)
{
	if (ft_strcmp(command, "exit") == 0 OR ft_strcmp(command, "export") == 0 \
	OR ft_strcmp(command, "unset") == 0 OR ft_strcmp(command, "cd") == 0)
		return (true);
	return (false);
}

void
	execute_special_builtins(t_minishell *minishell)
{
	if (ft_strcmp(minishell->commands[0].command[0], "exit") == 0)
		builtin_exit(minishell, 0);
	else if (ft_strcmp(minishell->commands[0].command[0], "unset") == 0)
		minishell->exit_code = builtin_unset(minishell, 0);
	else if (ft_strcmp(minishell->commands[0].command[0], "export") == 0)
		minishell->exit_code = builtin_export(minishell, 0);
	else if (ft_strcmp(minishell->commands[0].command[0], "cd") == 0)
		minishell->exit_code = builtin_cd(minishell, 0);
}

void
	execute_builtins(t_minishell *minishell, char *command, int i)
{
	int	return_value;

	return_value = 0;
	if (ft_strcmp(command, "exit") == 0 AND minishell->number_of_commands == 1)
		builtin_exit(minishell, i);
	else if (ft_strcmp(command, "pwd") == 0)
		builtin_pwd(minishell, i);
	else if (ft_strcmp(command, "env") == 0)
		builtin_env(minishell, i);
	else if (ft_strcmp(command, "export") == 0 \
	AND minishell->number_of_commands == 1)
		return_value = builtin_export(minishell, i);
	else if (ft_strcmp(command, "unset") == 0 \
	AND minishell->number_of_commands == 1)
		return_value = builtin_unset(minishell, i);
	else if (ft_strcmp(command, "echo") == 0)
		builtin_echo(minishell, i);
	else if (ft_strcmp(command, "cd") == 0)
		return_value = builtin_cd(minishell, i);
	exit(return_value);
}
