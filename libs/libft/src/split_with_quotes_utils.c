/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 17:29:02 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	return_value_after_quote(const char *string, int i)
{
	int		tmp;
	char	type;

	type = string[i];
	tmp = i;
	i++;
	// sdebug("couscous");
	// printf("\n\n\ni: %d, taille: %d\n\n\n", i, ft_strlen(string));
	while (string[i] != EOS AND string[i] != type)
		i++;
	if (i == ft_strlen(string))
		error("quotes", 1);
	return (i - tmp + 1);
}
