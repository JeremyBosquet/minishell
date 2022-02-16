/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:15:43 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 18:16:07 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	check_pipe(char *new_line)
{
	int	i;
	int	only_space_before_pipe;

	i = 0;
	only_space_before_pipe = 1;
	while (new_line[i])
	{
		if (new_line[i] != '|' AND new_line[i] != ' ')
			only_space_before_pipe = -1;
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i) - 1;
		else if (new_line[i] == '|')
		{
			if (only_space_before_pipe == 1)
				return (rerror("syntax error: ", "near unexpected token `|'"\
				, 1));
			else
				only_space_before_pipe = 1;
		}
		i++;
	}
	if (only_space_before_pipe == 1)
		return (2);
	return (EXIT_SUCCESS);
}
