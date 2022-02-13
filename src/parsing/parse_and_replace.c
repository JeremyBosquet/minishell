/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_replace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:17:18 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/13 18:57:44 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Probleme si $'test' et "$'test'" pas le même resultat

static int
	env_allow(char c)
{
	if (((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		|| (c == '_')
		|| (c >= '0' && c <= '9'))
	{
		return (1);
	}
	else
		return (0);
}

static char
	*parse_when_dollar(char *string, int *i, t_minishell *minishell)
{
	int		tmp;
	char	*memo;

	tmp = *i + 1;
	memo = NULL;
	if (string[tmp] && (env_allow(string[tmp]) || string[tmp] == '?'))
	{
		if (string[tmp] == '?')
		{
			*i += 2;
			if (*i < ft_strlen(string))
				memo = ft_substr(string, *i, ft_strlen(string) - *i, minishell->garbage);
			string[tmp - 1] = EOS;
			string = ft_strfjoin(string, ft_itoa(minishell->exit_code), 3, minishell->garbage);
			*i = ft_strlen(string);
			if (memo)
				string = ft_strfjoin(string, memo, 2, minishell->garbage);
		}
		else if (string[*i + 1] && ft_isspace(string[*i + 1]))
		{
			string = add_char(string, string[*i], minishell->garbage);
			*i += 1;
		}
		else
		{
			if (string[*i])
			{
				char *subline;

				*i += 1;
				while (string[*i] && env_allow(string[*i]))
					*i += 1;
				if (*i < ft_strlen(string))
					memo = ft_substr(string, *i, ft_strlen(string) - *i, minishell->garbage);
				subline = ft_substr(string, tmp, (size_t)*i - tmp, minishell->garbage);
				string[tmp - 1] = EOS;
				if (get_env_value(subline, minishell))
					string = ft_strfjoin(string, get_env_value(subline, minishell), 2, minishell->garbage);
				*i = ft_strlen(string);
				if (memo)
					string = ft_strfjoin(string, memo, 2, minishell->garbage);
			}
		}
	}
	else if (string[*i + 1] == '\'' || string[*i + 1] == '"')
	{
		*i += 1;
		if (*i < ft_strlen(string))
			memo = ft_substr(string, *i, ft_strlen(string) - *i, minishell->garbage);
		string[tmp - 1] = EOS;
		*i = ft_strlen(string);
		if (memo)
			string = ft_strfjoin(string, memo, 2, minishell->garbage);
	}
	else
		*i += 1;
	return (string);
}

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
	while (string[*i] != '"')
	{
		if (string[*i] == '$' && string[*i + 1] != '"' && (env_allow(string[*i + 1]) || string[*i + 1] == '?'))
			string = parse_when_dollar(string, i, minishell);
		else
			*i += 1;
	}
	if (string[*i] == '"')
	{
		string[*i] = EOS;
		string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	}
	return (string);
}

static char
	*replace_values(char *string, t_minishell *minishell)
{
	int		i;
	char	*new_line;

	i = -1;
	new_line = NULL;
	while (string[++i])
	{
		while (string[i] == '$' || string[i] == '\'' || string[i] == '"')
		{
			if (string[i] && string[i] == '$')
				string = parse_when_dollar(string, &i, minishell);
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

char
	*ft_parse_and_replace(char *line, t_minishell *minishell)
{
	char	*new_line;

	new_line = NULL;
	line = replace_values(line, minishell);
	return (line);
}

void
	replace_env(t_minishell *minishell)
{
	int	i;
	int	j;

	i = 0;
	while (i < minishell->number_of_commands)
	{
		j = 0;
		while (minishell->commands[i].command[j])
		{
			minishell->commands[i].command[j] = \
			ft_parse_and_replace(minishell->commands[i].command[j], minishell);
			j++;
		}
		i++;
	}
}
