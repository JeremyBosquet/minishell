/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:45:56 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/16 19:46:09 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
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
