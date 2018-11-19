/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convwchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/01 16:39:25 by bbrunell          #+#    #+#             */
/*   Updated: 2016/06/01 16:39:27 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convwchar(unsigned int nbr)
{
	char	*str;

	str = ft_strnew(4);
	if (nbr <= 0x7F)
		str[0] = nbr;
	else if (nbr <= 0x7FF)
	{
		str[0] = ((nbr >> 6) + 0xC0);
		str[1] = ((nbr & 0x3F) + 0x80);
	}
	else if (nbr <= 0xFFFF)
	{
		str[0] = ((nbr >> 12) + 0xE0);
		str[1] = (((nbr >> 6) & 0x3F) + 0x80);
		str[2] = ((nbr & 0x3F) + 0x80);
	}
	else if (nbr <= 0x1FFFFF)
	{
		str[0] = ((nbr >> 18) + 0xF0);
		str[1] = (((nbr >> 12) & 0x3F) + 0x80);
		str[2] = (((nbr >> 6) & 0x3F) + 0x80);
		str[3] = ((nbr & 0x3F) + 0x80);
	}
	return (str);
}

int		ft_wstrlen(unsigned int nbr)
{
	if (nbr <= 0x7F)
		return (1);
	else if (nbr <= 0x7FF)
		return (2);
	else if (nbr <= 0xFFFF)
		return (3);
	return (4);
}
