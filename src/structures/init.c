/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:41:36 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/18 21:24:46 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	get_number(t_minishell *minishell)
{
	int		number;
	char	*line;

	line = get_env_value("SHLVL", minishell);
	if (line == NULL)
		return (0);
	number = ft_atoi(line);
	if (number > 999)
	{
		printf("couscous: ");
		printf("warning: shell level (%d) too high, resetting to 1\n", \
		number + 1);
		number = 0;
	}
	free(line);
	return (number);
}

static void
	set_shlvl(t_minishell *minishell)
{
	int		n;
	char	*line;
	char	*number;

	n = get_number(minishell);
	if (n == 999)
		line = ft_strfjoin("SHLVL=", "", 0, minishell->garbage);
	else
	{
		number = ft_itoa(n + 1);
		if (number == NULL)
			return ;
		line = ft_strfjoin("SHLVL=", number, 2, minishell->garbage);
	}
	if (line == NULL)
		return ;
	minishell->environnement = add_to_environnement(minishell->environnement, \
	line, minishell->garbage);
	free(line);
}

bool
	init_minishell(t_minishell *minishell, char	**envp)
{
	char	*tmp;

	minishell->commands = NULL;
	minishell->pids = NULL;
	minishell->number_of_commands = 0;
	minishell->garbage = NULL;
	minishell->current_pwd = getcwd(NULL, 0);
	if (minishell->current_pwd == NULL)
		return (false);
	minishell->environnement = copy_environnement(envp, 0, \
	minishell->garbage);
	tmp = ft_strjoin("PWD=", minishell->current_pwd, minishell->garbage);
	minishell->environnement = add_to_environnement(minishell->environnement, \
	tmp, minishell->garbage);
	free(tmp);
	minishell->environnement = delete_line_in_environnement(\
	minishell->environnement, "OLDPWD", minishell->garbage);
	set_shlvl(minishell);
	minishell->env_export = copy_environnement(minishell->environnement, 0, \
	minishell->garbage);
	g_exit_code = 0;
	minishell->is_running = true;
	return (true);
}
