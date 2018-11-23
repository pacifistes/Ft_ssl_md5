/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_len.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 15:50:12 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 21:24:15 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			base_len(unsigned long long int value, int base)
{
	int y;
	int i;

	i = 1;
	y = base - 1;
	while (value > (unsigned long long int)y)
	{
		i++;
		value = value / base;
	}
	return (i);
}
