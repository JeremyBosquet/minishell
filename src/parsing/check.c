/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:58:24 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/09 15:31:01 by jbosquet         ###   ########.fr       */
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

static int
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
	{
		printf("couscous-0.1: syntax error on quotes\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int
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
		if (new_line[i] == '|')
		{
			if (only_space_before_pipe == 1)
			{
				printf("couscous-0.1: syntax error near unexpected token `|'\n");
				return (EXIT_FAILURE);
			}
			else
				only_space_before_pipe = 1;
		}
		i++;
	}
	if (only_space_before_pipe == 1)
		return (2);
	return (EXIT_SUCCESS);
}

char *
	check_new_line(char *new_line)
{
	char	*heredoc;

	if (ft_strlen(new_line) == 0)
		return (NULL);
	if (check_pipe(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_quotes(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_pipe(new_line) == 2)
	{
		heredoc = readline("> ");
		if (heredoc == NULL)
		{
			printf("couscous-0.1: syntax error: unexpected end of file\n");
			return (NULL);
		}
		new_line = ft_strjoin(new_line, heredoc);
		new_line = check_new_line(new_line);
	}
	return (new_line);
}
