/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_chevrons.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 18:18:11 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 18:54:45 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	check_chevrons_between(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if ((new_line[i] == '>' || new_line[i] == '<') && \
		new_line[i + 1] && new_line[i + 1] == ' ')
		{
			i++;
			while (new_line[i] && new_line[i] == ' ')
				i++;
			if (!new_line[i])
				break ;
			else if (new_line[i] == '<')
				return (rerror(S_ERROR, "near unexpected token `<'", 1));
			else if (new_line[i] == '>')
				return (rerror(S_ERROR, "near unexpected token `>'", 1));
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

static int
	check_chevrons_invalid2(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if ((new_line[i] == '>' || new_line[i] == '<') \
		&& new_line[i + 1] && new_line[i + 1] == ' ')
		{
			i++;
			while (new_line[i] && new_line[i] == ' ')
				i++;
			if (new_line[i] && new_line[i] == '|')
				return (rerror(S_ERROR, "near unexpected token `|'", 1));
			if (!new_line[i])
				break ;
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}

int
	check_chevrons_invalid(char *new_line)
{
	int	i;

	i = 0;
	while (new_line[i])
	{
		if (new_line[i] == '\'' || new_line[i] == '"')
			i += return_value_after_quote(new_line, i);
		else if (new_line[i] == '>' && new_line[i + 1] \
		&& new_line[i + 1] == '<')
			return (rerror(S_ERROR, "near unexpected token `<'", 1));
		else
			i++;
	}
	return (check_chevrons_invalid2(new_line));
}

static int
	check_chevrons_invalid_number2(char *new_line, int i)
{
	if (new_line[i] == '>' && new_line[i + 1] && new_line[i + 1] == '>' \
	&& new_line[i + 2] && (new_line[i + 2] == '>' || new_line[i + 2] == '<'))
	{
		if (new_line[i + 2] == '<')
			return (rerror(S_ERROR, "near unexpected token `<'", 1));
		return (rerror(S_ERROR, "near unexpected token `>'", 1));
	}
	else if (new_line[i] == '<' && new_line[i + 1] && new_line[i + 1] == '<' \
	&& new_line[i + 2] && (new_line[i + 2] == '>' || new_line[i + 2] == '<'))
	{
		if (new_line[i + 2] == '<')
			return (rerror(S_ERROR, "near unexpected token `<'", 1));
		return (rerror(S_ERROR, "near unexpected token `>'", 1));
	}
	else if (new_line[i] == '<' && new_line[i + 1] && new_line[i + 1] == '>' \
	&& new_line[i + 2] && new_line[i + 2] == '>')
		return (rerror(S_ERROR, "near unexpected token `>'", 1));
	return (EXIT_SUCCESS);
}

int
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
