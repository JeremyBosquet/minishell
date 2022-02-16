/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:55:20 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 18:56:31 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	check_quotes2(char *new_line, int *i, int *sp_quotes, int *db_quotes)
{
	while (new_line[*i])
	{
		if (new_line[*i] == '\'')
		{
			*sp_quotes = -*sp_quotes;
			*i += return_value_after_quote(new_line, *i);
			if (new_line[*i - 1] == '\'')
				*sp_quotes = -*sp_quotes;
			if (*i >= ft_strlen(new_line))
				break ;
		}
		else if (new_line[*i] == '"')
		{
			*db_quotes = -*db_quotes;
			*i += return_value_after_quote(new_line, *i);
			if (new_line[*i - 1] == '"')
				*db_quotes = -*db_quotes;
			if (*i >= ft_strlen(new_line))
				break ;
		}
		else
			*i += 1;
	}
	return (EXIT_SUCCESS);
}

int
	check_quotes(char *new_line)
{
	int	i;
	int	simple_quotes;
	int	double_quotes;

	i = 0;
	simple_quotes = 1;
	double_quotes = 1;
	check_quotes2(new_line, &i, &simple_quotes, &double_quotes);
	if (simple_quotes != 1 OR double_quotes != 1)
		return (rerror(S_ERROR, "near unclosed quotes", 1));
	return (EXIT_SUCCESS);
}
