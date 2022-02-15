/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:41:36 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/13 17:42:27 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	set_shlvl(t_minishell *minishell)
{
	int		n;
	char	*line;
	char	*number;

	line = get_env_value("SHLVL", minishell);
	if (line == NULL)
		return ;
	n = ft_atoi(line);
	free(line);
	number = ft_itoa(n + 1);
	if (number == NULL)
		return ;
	line = ft_strdup("SHLVL=", minishell->garbage);
	if (line == NULL)
		return ;
	line = ft_strfjoin(line, number, 3, minishell->garbage);
	if (line == NULL)
		return ;
	minishell->environnement = add_to_environnement(minishell->environnement, \
	line, minishell->garbage);
	free(line);
}

bool
	init_minishell(t_minishell *minishell, char	**envp)
{
	minishell->commands = NULL;
	minishell->pids = NULL;
	minishell->number_of_commands = 0;
	minishell->garbage = NULL;
	minishell->environnement = copy_environnement(envp, 0, \
	minishell->garbage);
	minishell->environnement = delete_line_in_environnement(\
	minishell->environnement, "OLDPWD", minishell->garbage);
	set_shlvl(minishell);
	g_exit_code = 0;
	minishell->is_running = true;
	return (true);
}
