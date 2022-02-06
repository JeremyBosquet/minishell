/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 17:40:26 by jbosquet         ###   ########.fr       */
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
	int			i;
	char		*arg;

	i = 0;
	arg = ft_strdup(argv[1]);
	(void) argc;
	(void) argv;
	if (!init_minishell(&minishell, envp))
		return ((printf("Couscous: initialization error.") * 0) + 1);
	while (minishell.is_running)
	{
		new_line = readline(RED"couscous > "END);
		i = 0;
		while (minishell.env[i])
		{
			printf("%s\n", minishell.env[i]);
			i++;
		}
		minishell.is_running = false;
	}
	free(arg);
	free(new_line);
	free_array((void **) minishell.env, i);
	return (0);
}
