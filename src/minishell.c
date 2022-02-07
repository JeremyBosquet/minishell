/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 20:00:36 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char		*new_line;

	(void) argv;
	check_argument(argc);
	if (init_minishell(&minishell, envp) == false)
		error("initialization error", 1);
	while (minishell.is_running == true)
	{
		new_line = readline(ORANGE"couscous-0.1$ "END);
		minishell.is_running = false;
	}
	free(new_line);
	clean_minishell(&minishell);
	return (0);
}
