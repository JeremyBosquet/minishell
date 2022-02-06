/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/05 16:10:27 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int
	wlength(char *string, char charset)
{
	int	words_length;

	words_length = 0;
	while (string[words_length] != EOS AND string[words_length] != charset)
		words_length += 1;
	return (words_length);
}

static int
	wcount(char *string, char charset)
{
	int	words_number;
	int	words_length;

	words_number = 0;
	while (*string != EOS)
	{
		while (*string != EOS AND *(string) == charset)
			string += 1;
		words_length = wlength(string, charset);
		string += words_length;
		if (words_length)
			words_number += 1;
	}
	return (words_number);
}

char
	**ft_split(const char *string, char charset)
{
	char	**array;
	int		i;
	int		words_number;
	int		words_length;

	if (string == NULL)
		return (NULL);
	words_number = wcount((char *) string, charset);
	array = ft_calloc(words_number + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < words_number)
	{
		while (*(string) != EOS AND *(string) == charset)
			string += 1;
		words_length = wlength((char *) string, charset);
		array[i] = ft_strndup(string, words_length);
		if (array[i] == NULL)
			free_array((void **) array, i);
		string += words_length;
		i += 1;
	}
	return (array);
}
