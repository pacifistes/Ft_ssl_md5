/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:11:55 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/27 10:18:29 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*tmp2;
	size_t			i;

	if (dest < src)
		return (ft_memcpy(dest, src, n));
	tmp = (unsigned char *)src;
	tmp2 = (unsigned char *)dest;
	i = n;
	while (i > 0)
	{
		tmp2[i - 1] = tmp[i - 1];
		i--;
	}
	return (dest);
}
