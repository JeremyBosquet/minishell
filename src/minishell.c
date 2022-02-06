/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 18:07:03 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =================== FAIT ===================
// Environments

int
	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char		*new_line;

	(void) argc;
	(void) argv;
	if (argc > 1)
		return (EXIT_FAILURE);
	if (!init_minishell(&minishell, envp))
		return ((printf("Couscous: initialization error.") * 0) + 1);
	while (minishell.is_running)
	{
		new_line = readline(RED"couscous > "END);
		minishell.is_running = false;
	}
	free(new_line);
	free_minishell(&minishell);
	return (0);
}
