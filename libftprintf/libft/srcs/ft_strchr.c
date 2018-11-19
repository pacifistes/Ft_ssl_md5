/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 09:46:25 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/19 17:26:50 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return ((char*)s + i);
	return (NULL);
}
