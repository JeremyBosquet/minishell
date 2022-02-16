/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:17:18 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 19:46:18 by jbosquet         ###   ########.fr       */
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
	*dollar_replace(char *string, int *i, int *tmp, t_minishell *minishell)
{
	char	*subline;
	char	*memo;

	memo = NULL;
	*i += 1;
	while (string[*i] && env_allow(string[*i]))
		*i += 1;
	if (*i < ft_strlen(string))
		memo = ft_substr(string, *i, ft_strlen(string) - *i, \
		minishell->garbage);
	subline = ft_substr(string, *tmp, *i - *tmp, minishell->garbage);
	string[*tmp - 1] = EOS;
	if (get_env_value(subline, minishell))
		string = ft_strfjoin(string, get_env_value(subline, minishell), 3, \
		minishell->garbage);
	*i = ft_strlen(string);
	if (memo)
		string = ft_strfjoin(string, memo, 3, minishell->garbage);
	return (string);
}

static char
	*dollar_interogative(char *string, int *i, int *tmp, t_minishell *minishell)
{
	char	*memo;

	memo = NULL;
	*i += 2;
	if (*i < ft_strlen(string))
		memo = ft_substr(string, *i, ft_strlen(string) - *i, \
		minishell->garbage);
	string[*tmp - 1] = EOS;
	string = ft_strfjoin(string, ft_itoa(g_exit_code), 3, \
	minishell->garbage);
	*i = ft_strlen(string);
	if (memo)
		string = ft_strfjoin(string, memo, 3, minishell->garbage);
	return (string);
}

static char
	*dollar_quotes_after(char *string, int *i, int *tmp, t_minishell *minishell)
{
	char	*memo;

	memo = NULL;
	*i += 1;
	if (*i < ft_strlen(string))
		memo = ft_substr(string, *i, ft_strlen(string) - *i, \
		minishell->garbage);
	string[*tmp - 1] = EOS;
	*i = ft_strlen(string);
	if (memo)
		string = ft_strfjoin(string, memo, 3, minishell->garbage);
	return (string);
}

char
	*parse_when_dollar(char *string, int *i, t_minishell *minishell)
{
	int		tmp;
	char	*memo;

	tmp = *i + 1;
	memo = NULL;
	if (string[tmp] && (env_allow(string[tmp]) || string[tmp] == '?'))
	{
		if (string[tmp] == '?')
			string = dollar_interogative(string, i, &tmp, minishell);
		else
			if (string[*i])
				string = dollar_replace(string, i, &tmp, minishell);
	}
	else if (*i > 0 && (string[*i - 1] == '\'' || string[*i - 1] == '"') \
	&& (string[*i + 1] == '"' || string[*i + 1] == '\''))
		*i += 1;
	else if (string[*i + 1] == '\'' || string[*i + 1] == '"')
		string = dollar_quotes_after(string, i, &tmp, minishell);
	else
		*i += 1;
	return (string);
}
