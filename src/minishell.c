/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 15:36:42 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell2.h"

static void
	cleanup(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->number_of_commands)
	{
		free_array((void **) minishell->commands[i].command, \
		size_of_array(minishell->commands[i].command));
		i++;
	}
	if (minishell->number_of_commands > 0)
		free(minishell->commands);
	minishell->number_of_commands = 0;
}

//TODO: Free les commandes et tout ce qu'il y a dedans.
int
	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;
	char		*new_line;

	(void) argv;
	check_number_of_argument(argc);
	if (init_minishell(&minishell, envp) == false)
		error("initialization error", 1);
	my_signal();
	while (minishell.is_running == true)
	{
		new_line = readline(ORANGE"couscous-0.1$ "END);
		if (new_line == NULL)
			break ;
		add_history(new_line);
		parse_new_line(&minishell, new_line);
		if (minishell.number_of_commands == 1 \
		AND is_special_builtins(minishell.commands[0].command[0]) == true)
			execute_special_builtins(&minishell);
		else
			execute(&minishell);
		cleanup(&minishell);
	}
	clean_minishell(&minishell);
	printf("exit\n");
	return (minishell.exit_code);
}
