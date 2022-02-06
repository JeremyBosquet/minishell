/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 17:00:37 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// =================== ENVIRONMENT ===================
//FIND env var name
//REPLACE env
//DELETE env

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
	minishell.is_running = true;
	minishell.env = copy_env(envp, 0);
	while (minishell.is_running)
	{
		minishell.env = add_env(minishell.env, "test=test");
		minishell.env = add_env(minishell.env, "test1=test");
		minishell.env = replace_env(minishell.env, find_env(minishell.env, arg), "bonjour");
		minishell.env = delete_env(minishell.env, arg);
		new_line = readline(RED"couscous > "END);
		printf("%d", find_env(minishell.env, arg));
		while (minishell.env[i])
		{
			printf("%d: %s\n", i, minishell.env[i]);
			i++;
		}
		minishell.is_running = false;
	}
	// free(arg);
	free_array((void **) minishell.env, i);
	return (0);
}
