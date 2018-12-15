/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:12:00 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/15 19:17:00 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0')
	{
		dst[i] = (unsigned char)src[i];
		i++;
	}
	dst[i] = (unsigned char)src[i];
	return (dst);
}
