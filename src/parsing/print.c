/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:37:24 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/10 15:59:13 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < minishell->number_of_commands)
	{
		j = 0;
		printf(ORANGE"========= Command %d =========\n"END, i);
		while (minishell->commands[i].command[j])
		{
			printf("%s\n", minishell->commands[i].command[j]);
			j++;
		}
		i++;
	}
	printf(ORANGE"=============================");
	printf(END);
	printf("\n");
}

void	print_command(char **str)
{
	int	i;

	i = 0;
	printf(ORANGE"========= Command =========\n"END);
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
	printf(ORANGE"===========================");
	printf(END);
	printf("\n");
}
