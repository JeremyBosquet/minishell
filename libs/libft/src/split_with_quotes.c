/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/16 22:21:50 by mmosca           ###   ########lyon.fr   */
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

static int
	wlength(const char *string, char charset)
{
	int	length;

	length = 0;
	while (string[length] != '\0')
	{
		if (string[length] == charset)
			break ;
		if (string[length] == '\'' || string[length] == '"')
			length += return_value_after_quote(string, length);
		else if ((string[length] == '>' || string[length] == '<') \
		&& charset != '|' && length > 0)
			break ;
		else if (string[length] == '>' && charset != '|')
			return (wlength3(string, &length));
		else if (string[length] == '<' && charset != '|')
			return (wlength2(string, &length));
		else
			length += 1;
	}
	return (length);
}

static unsigned int
	wcount(const char *string, char charset)
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

char	**ft_split_with_quotes(char const *s, char c, t_list *garbage)
{
	char	**str_split;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	str_split = (char **)ft_calloc((wcount(s, c) + 1), sizeof(char *), garbage);
	if (!str_split)
		return (0);
	while (i <= wcount(s, c))
	{
		while (s[j] && s[j] == c)
			j++;
		if (s[j])
		{
			str_split[i] = ft_word_dup(s, j, j + wlength(&s[j], c), garbage);
			if (!str_split[i])
				return (ft_clear_split(i, str_split));
			j += wlength(&s[j], c);
		}
		i++;
	}
	return (str_split);
}
