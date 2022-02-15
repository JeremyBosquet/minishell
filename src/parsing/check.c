/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 13:58:24 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/14 20:18:38 by jbosquet         ###   ########.fr       */
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
		return (rerror("syntax error: ", "near unclosed quotes", 1));
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
				return (rerror("syntax error: ", "near unexpected token `|'", 1));
			else
				only_space_before_pipe = 1;
		}
		i++;
	}
	if (only_space_before_pipe == 1)
		return (2);
	return (EXIT_SUCCESS);
}

int
	check_space(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] != ' ')
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

char *
	add_space_after_chevron(char *new_line, t_list *garbage)
{
	int		i;
	char	*memo;

	i = 0;
	while(new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if ((new_line[i] == '>' || new_line[i] == '<') 
			&& new_line[i + 1] && new_line[i + 1] == '$')
		{
			i += 1;
			memo = ft_substr(new_line, i, ft_strlen(new_line) - i, garbage);
			new_line[i] = EOS;
			new_line = ft_strfjoin(new_line, " ", 1, garbage);
			i = ft_strlen(new_line);
			if (memo)
				new_line = ft_strfjoin(new_line, memo, 2, garbage);
		}
		else
			i++;
	}
	return (new_line);
}

static int
	check_chevrons_invalid(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if (new_line[i] == '>' && new_line[i + 1] && new_line[i + 1] == '<')
			return (rerror("syntax error: ", "near unexpected token `<'", 1));
		else
			i++;
	}
	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if ((new_line[i] == '>' || new_line[i] == '<') && new_line[i + 1] && new_line[i + 1] == ' ')
		{
			i++;
			while (new_line[i] && new_line[i] == ' ')
				i++;
			if (new_line[i] && new_line[i] == '|')
				return (rerror("syntax error: ", "near unexpected token `|'", 1));
			if (!new_line[i])
				break;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

static int
	check_chevrons_invalid_end(char *new_line)
{
	int	i;

	i = ft_strlen(new_line) - 1;
	while (i > 0)
	{
		if (new_line[i] == ' ')
			i--;
		else if (new_line[i] == '<' || new_line[i] == '>')
			return (rerror("syntax error: ", "near unexpected token `newline'", 1));
		else
			break ;
	}
	return (EXIT_SUCCESS);
}

static int
	check_chevrons_invalid_number2(char *new_line, int i)
{
	if (new_line[i] == '>' && new_line[i + 1] && new_line[i + 1] == '>' \
	&& new_line[i + 2] && (new_line[i + 2] == '>' || new_line[i + 2] == '<'))
	{
		if (new_line[i + 2] == '<')
			return (rerror("syntax error: ", "near unexpected token `<'", 1));
		return (rerror("syntax error: ", "near unexpected token `>'", 1));
	}
	else if (new_line[i] == '<' && new_line[i + 1] && new_line[i + 1] == '<' \
	&& new_line[i + 2] && (new_line[i + 2] == '>' || new_line[i + 2] == '<'))
	{
		if (new_line[i + 2] == '<')
			return (rerror("syntax error: ", "near unexpected token `<'", 1));
		return (rerror("syntax error: ", "near unexpected token `>'", 1));
	}
	else if (new_line[i] == '<' && new_line[i + 1] && new_line[i + 1] == '>' \
	&& new_line[i + 2] && new_line[i + 2] == '>')
		return (rerror("syntax error: ", "near unexpected token `>'", 1));
	return (EXIT_SUCCESS);
}
static int
	check_chevrons_invalid_number(char *new_line)
{
	int		i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if (new_line[i] == '>' || new_line[i] == '<')
		{
			if (check_chevrons_invalid_number2(new_line, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

static int
	check_chevrons(char *new_line)
{
	if (check_chevrons_invalid_end(new_line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_chevrons_invalid(new_line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_chevrons_invalid_number(new_line) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char *
	check_new_line(char *new_line, t_list *garbage)
{
	char	*heredoc;

	if (new_line == NULL)
		return (NULL);
	if (ft_strlen(new_line) == 0)
		return (NULL);
	if (check_pipe(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_quotes(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_space(new_line) == EXIT_FAILURE)
		return (NULL);
	new_line = add_space_after_chevron(new_line, garbage);
	if (check_chevrons(new_line) == EXIT_FAILURE)
		return (NULL);
	if (check_pipe(new_line) == 2)
	{
		heredoc = readline("> ");
		if (heredoc == NULL)
			rerror("syntax error: ", "unexpected end of file", 0);
		new_line = ft_strfjoin(new_line, heredoc, 3, garbage);
		new_line = check_new_line(new_line, garbage);
	}
	return (new_line);
}
