/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 10:30:39 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/18 20:18:24 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	builtin_pwd(t_minishell *minishell, int i)
{
	char	*pwd;

	if (minishell->commands[i].command[1] != NULL)
		if (minishell->commands[i].command[1][0] == '-')
			error_exe(minishell->commands[i].command[0], \
			minishell->commands[i].command[1], "invalid option", 1);
	free(minishell->current_pwd);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		pwd = ft_strdup(minishell->current_pwd, minishell->garbage);
	else
		minishell->current_pwd = ft_strdup(pwd, minishell->garbage);
	printf("%s\n", pwd);
	free(pwd);
	g_exit_code = 0;
}
