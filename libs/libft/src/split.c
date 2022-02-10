/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 11:16:23 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_word_dup(const char *str, int start, int finish, t_list *g)
{
	char	*word;
	int		i;

	i = 0;
	word = ft_calloc((finish - start + 1), sizeof(char), g);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static unsigned int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != 0 && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (s[i])
			i++;
	}
	return (count);
}

static int	ft_len_word(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**ft_clear_split(int n, char **split)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (0);
}

char	**ft_split(char const *s, char c, t_list *g)
{
	char	**str_split;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	str_split = ft_calloc((ft_count_words(s, c) + 1), sizeof(char *), g);
	if (!str_split)
		return (0);
	while (i <= ft_count_words(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j])
		{
			str_split[i] = ft_word_dup(s, j, j + ft_len_word(&s[j], c), g);
			if (!str_split[i])
				return (ft_clear_split(i, str_split));
			j += ft_len_word(&s[j], c);
		}
		i++;
	}
	return (str_split);
}
