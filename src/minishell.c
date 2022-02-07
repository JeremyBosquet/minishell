/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 11:19:35 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		minishell.is_running = false;
	}
	free(new_line);
	clean_minishell(&minishell);
	printf("exit\n");
	return (0);
}
