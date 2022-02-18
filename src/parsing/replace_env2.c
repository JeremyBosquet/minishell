/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:45:56 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/18 19:26:11 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	not_replace_if_heredoc(char *new_line, int *i)
{
	if (new_line[*i] == '<' && new_line[*i +1] && new_line[*i + 1] == '<')
	{
		*i += 2;
		while (new_line[*i] != EOS && new_line[*i] == ' ')
			*i += 1;
		while (new_line[*i] != EOS)
		{
			if (new_line[*i] == '"' || new_line[*i] == '\'')
				*i += return_value_after_quote(new_line, *i);
			else if (new_line[*i] == EOS || new_line[*i] == ' ')
				break ;
			else
				*i += 1;
		}
	}
}

char
	*replace_values(char *string, t_minishell *minishell)
{
	int		i;
	char	*new_line;
	bool	in_doubles;

	i = -1;
	new_line = NULL;
	in_doubles = false;
	while (string[++i])
	{
		if (string[i] == '"')
			in_doubles = !in_doubles;
		not_replace_if_heredoc(string, &i);
		while (string[i] == '$' || (string[i] == '\'' && in_doubles == false))
		{
			if (string[i] == '\'')
				i += return_value_after_quote(string, i);
			else if (string[i] && string[i] == '$')
				string = parse_when_dollar(string, &i, minishell);
			if (i >= ft_strlen(string))
				break ;
		}
		if (i >= ft_strlen(string))
			break ;
	}
	return (string);
}

void
	replace_env(char **tabs, t_minishell *minishell)
{
	int	i;

	i = 0;
	while (tabs[i])
	{
		tabs[i] = replace_values(tabs[i], minishell);
		i++;
	}
}
