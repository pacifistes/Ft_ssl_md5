/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:35:10 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 10:11:36 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
		i++;
	while ((unsigned char)s2[j] != '\0' && (int)n > j)
	{
		s1[i] = (unsigned char)s2[j];
		i++;
		j++;
	}
	s1[i] = '\0';
	return (s1);
}
