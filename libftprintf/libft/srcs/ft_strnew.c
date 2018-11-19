/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 10:06:00 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 10:06:07 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*new;
	size_t	i;

	new = (char*)malloc(sizeof(char) * (size + 1));
	i = 0;
	if (!new)
		return (NULL);
	while (i < size + 1)
	{
		new[i] = '\0';
		i++;
	}
	return (new);
}
