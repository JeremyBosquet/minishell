/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:12:18 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/18 19:51:26 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	cleanup(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (i < minishell->number_of_commands)
	{
		if (minishell->commands[i].type_infile == HEREDOC \
		&& access(minishell->commands[i].file_in, F_OK) == 0 \
		&& unlink(minishell->commands[i].file_in) != 0)
			perror("unlink error");
		if (minishell->commands[i].file_in)
			free(minishell->commands[i].file_in);
		if (minishell->commands[i].file_out)
			free(minishell->commands[i].file_out);
		free_array((void **) minishell->commands[i].command, \
		size_of_array(minishell->commands[i].command));
		i++;
	}
	if (minishell->number_of_commands > 0)
		free(minishell->commands);
	minishell->number_of_commands = 0;
}

static void
	main_loop(t_minishell *minishell)
{
	char	*new_line;

	while (minishell->is_running == true)
	{
		new_line = readline(ORANGE"couscous-0.1$ "END);
		if (new_line == NULL)
			break ;
		if (new_line[0] != '\0')
		{
			add_history(new_line);
			parse_new_line(minishell, new_line);
		}
		if (minishell->number_of_commands == 1 \
		AND is_special_builtins(minishell->commands[0].command[0]) == true)
			execute_special_builtins(minishell);
		else
			execute(minishell);
		cleanup(minishell);
	}
}

int
	main(int argc, char **argv, char **envp)
{
	t_minishell	minishell;

	(void) argv;
	check_number_of_argument(argc);
	if (init_minishell(&minishell, envp) == false)
		error("initialization error", 1);
	my_signal();
	main_loop(&minishell);
	clean_minishell(&minishell);
	printf("\033[1A\033[14Cexit\n");
	return (g_exit_code);
}
