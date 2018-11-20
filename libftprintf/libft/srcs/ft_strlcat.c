/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:17:38 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 09:49:18 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;

	i = 0;
	while (dst[i])
	{
		++i;
		if (i > size)
			return (size + ft_strlen(src));
	}
	while (*src && i < size - 1)
	{
		dst[i] = *src;
		++i;
		src = src + 1;
	}
	dst[i] = '\0';
	return (ft_strlen(dst) + ft_strlen(src));
}
