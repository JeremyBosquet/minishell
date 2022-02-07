/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/07 18:11:12 by jbosquet         ###   ########.fr       */
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
	while (string[i] != EOS AND string[i] != type)
		i++;
	return (i - tmp + 1);
}
