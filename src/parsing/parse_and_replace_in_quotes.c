/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_replace_in_quotes.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 15:17:18 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/11 15:48:46 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int
// 	return_value_af_quotes(const char *string, int i)
// {
// 	int		tmp;
// 	char	type;

// 	type = string[i];
// 	tmp = i;
// 	i++;
// 	while (string[i] != EOS AND string[i] != type)
// 		i++;
// 	return (i - tmp + 1);
// }

// static int
// 	len_to_next_char(char *line, char c, int *i)
// {
// 	int	tmp;

// 	tmp = 0;
// 	while (line[*i + tmp] AND line[*i + tmp] != c)
// 		tmp++;
// 	return (tmp);
// }

// static int
// 	env_allow(char c)
// {
// 	if (((c >= 'a' && c <= 'z')
// 			|| (c >= 'A' && c <= 'Z'))
// 		|| (c == '_')
// 		|| (c >= '0' && c <= '9'))
// 	{
// 		return (1);
// 	}
// 	else
// 		return (0);
// }

static void
	parse_when_dollar(char **string, int *i, t_minishell *minishell)
{
	printf("%c\n", *string[*i + 1]);
	if (*string[*i + 1] == '$')
	{
		printf("%d\n", minishell->exit_code);
	}
	else if (ft_isspace(*string[*i + 1]))
	{
		add_char(*string, *string[*i], minishell->garbage);
	}
	else
	{
		*string = ft_strfjoin(*string, get_env_value("SHELL", minishell), 1, minishell->garbage);
	}
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
	*i -= 1;
	return (string);
}

static char
	*double_quotes_replace(char *string, int *i, t_minishell *minishell)
{
	string[*i] = '\0';
	string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	while (string[*i] != '"')
	{
		if (string[*i] == '$')
			parse_when_dollar(&string, i, minishell);
		*i += 1;
	}
	if (string[*i] == '"')
	{
		string[*i] = EOS;
		string = ft_strfjoin(string, &(string[*i + 1]), 1, minishell->garbage);
	}
	*i -= 1;
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
		if (string[i] == '\'')
			string = simple_quote_replace(string, &i, minishell);
		else if (string[i] == '"')
			string = double_quotes_replace(string, &i, minishell);
		else if (string[i] && string[i + 1] && string[i] == '$')
			parse_when_dollar(&string, &i, minishell);
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
