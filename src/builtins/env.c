/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 09:44:58 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/12 10:03:19 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

static void
	check_arguments_or_option(char **command)
{
	if (command[1][0] == '-')
	{
		printf("env: illegal option -- %c\n", command[1][1]);
		exit(1);
	}
	else
	{
		printf("env: %s: No such file or directory\n", command[1]);
		exit(127);
	}
}

void
	builtin_env(t_minishell *minishell, int i)
{
	int	j;

	if (size_of_array(minishell->commands[i].command) > 1)
		check_arguments_or_option(minishell->commands[i].command);
	j = 0;
	while (minishell->environnement[j] != NULL)
	{
		printf("%s\n", minishell->environnement[j]);
		j += 1;
	}
}
