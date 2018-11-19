/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 14:53:31 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/30 15:43:50 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_range(int min, int max)
{
	int size;
	int i;
	int *dest;

	dest = 0;
	i = 0;
	size = max - min;
	if (size < 0)
		size = -size;
	if (min == max || min > max)
		return (dest);
	dest = (int*)malloc(sizeof(*dest) * size);
	if (!dest)
		return (dest);
	while (min < max)
	{
		dest[i] = min;
		min++;
		i++;
	}
	return (dest);
}
