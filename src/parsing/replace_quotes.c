/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:39:21 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 19:43:37 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*simple_quote_replace(char *string, int *i, t_minishell *minishell)
{
	string[*i] = '\0';
	string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	while (string[*i] != '\'')
		*i += 1;
	if (string[*i] == '\'')
	{
		string[*i] = EOS;
		string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	}
	return (string);
}

static char
	*double_quotes_replace(char *string, int *i, t_minishell *minishell)
{
	string[*i] = '\0';
	string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	printf("\n%c\n", string[*i]);
	while (string[*i] != '"')
		*i += 1;
	if (string[*i] == '"')
	{
		string[*i] = EOS;
		string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	}
	return (string);
}

char
	*replace_values_quotes(char *string, t_minishell *minishell)
{
	int		i;
	char	*new_line;

	i = -1;
	new_line = NULL;
	while (string[++i])
	{
		while (string[i] == '\'' || string[i] == '"')
		{
			if (string[i] == '\'')
				string = simple_quote_replace(string, &i, minishell);
			if (string[i] == '"')
				string = double_quotes_replace(string, &i, minishell);
			if (i >= ft_strlen(string))
				break ;
		}
		if (i >= ft_strlen(string))
			break ;
	}
	return (string);
}
