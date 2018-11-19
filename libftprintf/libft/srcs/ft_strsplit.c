/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 10:39:01 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/30 10:41:46 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
		{
			j++;
			i++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (j);
}

static char		*add_word(size_t *i, char const *s, char c)
{
	size_t	size;
	size_t	j;
	char	*word;

	size = *i;
	j = 0;
	while (s[size] && s[size] != c)
		size++;
	word = ft_strnew(size - *i);
	if (word)
	{
		while (*i < size)
		{
			word[j] = s[*i];
			j++;
			*i = *i + 1;
		}
		return (word);
	}
	return (0);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		a;
	size_t		*i;
	size_t		j;

	a = 0;
	i = &a;
	j = 0;
	tab = NULL;
	if (s)
		tab = (char**)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (tab)
	{
		while (j < count_word(s, c))
		{
			while (s[*i] == c)
				*i = *i + 1;
			if (s[*i] != c && s[*i])
				tab[j++] = add_word(i, s, c);
		}
		tab[j] = 0;
		return (tab);
	}
	return (0);
}
