/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:34:30 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/11 16:10:43 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void
	strjoin_free(char *first_string, char *second_string, int nfree)
{
	if (nfree == 1)
		free(first_string);
	else if (nfree == 2)
		free(second_string);
	else if (nfree == 3)
	{
		free(first_string);
		free(second_string);
	}
	else
		return ;
}

char
	*ft_strjoin(const char *first_string, const char *second_string, t_list *g)
{
	int		i;
	int		j;
	char	*string;

	if (first_string == NULL OR second_string == NULL)
		return (NULL);
	string = ft_calloc(ft_strlen(first_string) + ft_strlen(second_string) + 1, \
	sizeof(char), g);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (first_string[i] != EOS)
	{
		string[i] = first_string[i];
		i += 1;
	}
	j = 0;
	while (second_string[j] != EOS)
	{
		string[i] = second_string[j];
		i += 1;
		j += 1;
	}
	string[i] = EOS;
	return (string);
}

char
	*ft_strfjoin(const char *first_string, const char *second_string, int nfree,
	t_list *garbage)
{
	int		i;
	int		j;
	char	*string;

	if (first_string == NULL OR second_string == NULL)
		return (NULL);
	string = ft_calloc(ft_strlen(first_string) + ft_strlen(second_string) + 1, \
	sizeof(char), garbage);
	if (string == NULL)
		return (NULL);
	i = 0;
	while (first_string[i] != EOS)
	{
		string[i] = first_string[i];
		i += 1;
	}
	j = 0;
	while (second_string[j] != EOS)
		string[i++] = second_string[j++];
	string[i] = EOS;
	strjoin_free((char *) first_string, (char *) second_string, nfree);
	return (string);
}
