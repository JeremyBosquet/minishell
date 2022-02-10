/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:30:39 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 13:12:06 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

// void
// 	builtins_pwd(t_minishell *minishell)
// {
// 	char	*working_directory;
// 	int		line;

// 	line = find_line_of_name(minishell->environnement, "PWD", \
// 	minishell->garbage);
// 	if (line == -1)
// 		return ;
// 	working_directory = get_value_of_line(minishell->environnement[line], \
// 	minishell->garbage);
// 	printf("%s\n", working_directory);
// 	free(working_directory);
// 	minishell->exit_code = 0;
// }

void
	builtins_pwd(t_minishell *minishell, int i)
{
	char	*pwd;

	if (minishell->commands[i].command[1] != NULL)
		error_exe(minishell->commands[i].command[0], \
		minishell->commands[i].command[1], "invalid option", 1);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return ;
	printf("%s\n", pwd);
	free(pwd);
	minishell->exit_code = 0;
}
