/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 17:00:45 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 10:17:10 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*map;

	i = 0;
	if (!s)
		return (NULL);
	map = ft_strnew(ft_strlen(s));
	if (map == NULL)
		return (NULL);
	while (*s)
	{
		map[i] = f(i, *s);
		i++;
		s++;
	}
	map[i] = '\0';
	return (map);
}
