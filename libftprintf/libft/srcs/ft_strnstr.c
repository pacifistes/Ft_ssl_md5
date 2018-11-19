/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:52:47 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/30 11:07:46 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[j])
	{
		while (s1[j] == s2[i] && s2[i] && j < (int)n)
		{
			i++;
			j++;
		}
		if (s2[i] == '\0')
			return ((char*)s1 + j - i);
		else
		{
			j = j - i;
			i = 0;
		}
		j++;
	}
	if (s1[j] == s2[i])
		return ((char*)s1 + j);
	return (NULL);
}
