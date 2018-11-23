/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:58:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:50:32 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa_base(unsigned long long int value, int base)
{
	int		len;
	char	*buf;

	len = base_len(value, base);
	if (value == 0)
		return (ft_strdup("0"));
	buf = ft_strnew(len);
	buf[len] = 0;
	len--;
	while (value > 0)
	{
		buf[len] = value % base + ((value % base > 9) ? ('a' - 10) : '0');
		value = value / base;
		len--;
	}
	return (buf);
}
