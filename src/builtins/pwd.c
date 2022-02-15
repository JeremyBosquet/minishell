/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:30:39 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/15 15:45:20 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

void
	builtin_pwd(t_minishell *minishell, int i)
{
	char	*pwd;

	if (minishell->commands[i].command[1] != NULL)
		if (minishell->commands[i].command[1][0] == '-')
			error_exe(minishell->commands[i].command[0], \
			minishell->commands[i].command[1], "invalid option", 1);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = ft_strdup(minishell->current_pwd, minishell->garbage);
	else
		minishell->current_pwd = ft_strdup(pwd, minishell->garbage);
	printf("%s\n", pwd);
	free(pwd);
	g_exit_code = 0;
}
