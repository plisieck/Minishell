/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plisieck <plisieck@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/14 19:36:28 by plisieck          #+#    #+#             */
/*   Updated: 2015/03/09 14:11:15 by plisieck         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_first_len(const char *s, char c1, char c2)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != c1 && s[i] != c2 && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static int	ft_find_words(const char *s, char c1, char c2)
{
	int	k;
	int	words;

	k = 0;
	words = 0;
	while (*s != '\0')
	{
		if (k == 1 && (*s == c1 || *s == c2))
			k = 0;
		if (k == 0 && *s != c1 && *s != c2)
		{
			k = 1;
			words++;
		}
		s++;
	}
	return (words);
}

char		**ft_strdoublesplit(char const *s, char c1, char c2)
{
	char	**ptr;
	int		nbr;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	nbr = ft_find_words(s, c1, c2);
	ptr = malloc(sizeof(*ptr) * nbr + 1);
	if (!ptr)
		return (NULL);
	while (nbr > 0)
	{
		while ((*s == c1 || *s == c2) && *s != '\0')
			s++;
		ptr[i] = ft_strsub(s, 0, ft_find_first_len((const char *)s, c1, c2));
		if (!ptr[i])
			return (NULL);
		s = s + ft_find_first_len(s, c1, c2);
		i++;
		nbr--;
	}
	ptr[i] = NULL;
	return (ptr);
}
