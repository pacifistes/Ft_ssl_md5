/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:58:32 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 12:58:35 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			countchar(unsigned long long int value, t_line *li)
{
	int y;
	int i;

	i = 1;
	y = li->base - 1;
	while (value > (unsigned long long int)y)
	{
		i++;
		value = value / li->base;
	}
	return (i);
}

char		*ft_itoa_base(unsigned long long int value, t_line *li)
{
	int		len;
	char	*buf;

	len = countchar(value, li);
	if (value == 0)
		return (ft_strdup("0"));
	buf = ft_strnew(len);
	buf[len] = 0;
	len--;
	while (value > 0)
	{
		if (li->x == 1)
			buf[len] = value % li->base + ((value % li->base > 9)
			? ('A' - 10) : '0');
		else
			buf[len] = value % li->base + ((value % li->base > 9)
			? ('a' - 10) : '0');
		value = value / li->base;
		len--;
	}
	return (buf);
}
