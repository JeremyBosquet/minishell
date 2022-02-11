/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 23:16:03 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/11 16:10:43 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	ft_strlen(const char *string)
{
	int	i;

	i = 0;
	while (string != NULL AND string[i] != EOS)
		i += 1;
	return (i);
}

char
	*ft_strdup(const char *string, t_list *garbage)
{
	char	*new;
	int		size;

	size = ft_strlen(string) + 1;
	new = ft_calloc(size, sizeof(char), garbage);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, string, size);
	return (new);
}

char
	*ft_strcpy(char *destination, char *source)
{
	int	i;

	i = 0;
	while (source[i] != '\0')
	{
		destination[i] = source[i];
		i += 1;
	}
	destination[i] = '\0';
	return (destination);
}

int
	ft_strcmp(char *first_string, char *second_string)
{
	int	i;

	i = 0;
	while (first_string[i] != EOS AND second_string[i] != EOS \
	AND first_string[i] == second_string[i])
		i += 1;
	return (first_string[i] - second_string[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_list *g)
{
	char			*newstr;
	unsigned int	i;
	unsigned int	j;

	i = start;
	j = 0;
	newstr = NULL;
	if (!s)
		return (0);
	if (len > (size_t)ft_strlen(s))
		len = ft_strlen(s);
	newstr = (char *)ft_calloc(sizeof(char), (len + 1), g);
	if (!newstr)
		return (0);
	if (start < (unsigned char)ft_strlen((char *)s))
	{
		while (i < (start + len) && s[i])
		{
			newstr[j] = s[i];
			j++;
			i++;
		}
	}
	newstr[j] = 0;
	return (newstr);
}
