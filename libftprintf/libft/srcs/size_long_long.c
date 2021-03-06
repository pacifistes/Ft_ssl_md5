/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_long_long.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 13:24:42 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/28 13:24:44 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	size_long_long(long long int n)
{
	int i;

	i = 0;
	if (n > (-9223372036854775807 - 1) && n <= 9223372036854775807)
	{
		if (n < 0)
		{
			i++;
			n = -n;
		}
		while (n > 9)
		{
			i++;
			n = n - (n % 10);
			n = n / 10;
		}
		i++;
	}
	if (n == (-9223372036854775807 - 1))
		i = 20;
	return (i);
}
