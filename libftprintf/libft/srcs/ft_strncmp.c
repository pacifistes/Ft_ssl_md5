/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 13:00:22 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 18:57:22 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && i < n && s1[i] == s2[i])
		i++;
	if (i >= n)
		return (((unsigned char)s1[i - 1]) - ((unsigned char)s2[i - 1]));
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
