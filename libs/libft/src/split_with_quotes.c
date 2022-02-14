/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 15:54:31 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/14 18:42:22 by jbosquet         ###   ########.fr       */
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
	int	words_length;

	words_length = 0;
	while (string[words_length] != '\0')
	{
		if (string[words_length] != charset)
		{
			if (string[words_length] == '\'' || string[words_length] == '"')
				words_length += return_value_after_quote(string, words_length);
			else if ((string[words_length] == '>' || string[words_length] == '<') && charset != '|' && words_length > 0)
				break ;
			else if (string[words_length] == '>' && charset != '|')
			{
				if (string[words_length + 1] == '>')
					words_length += 2;
				else
					if (string[words_length + 1] != '<')
						words_length += 1;
				break ;
			}
			else if (string[words_length] == '<' && charset != '|')
			{
				if (string[words_length + 1] == '<')
					words_length += 2;
				else
					if (string[words_length + 1] != '>')
						words_length += 1;
					else if (string[words_length + 1] == '>')
						words_length += 1;
				break ;
			}
			else
				words_length += 1;
		}
		else
			break ;
	}
	return (words_length);
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
