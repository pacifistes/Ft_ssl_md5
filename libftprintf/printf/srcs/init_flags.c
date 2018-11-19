/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:39:18 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/24 12:39:21 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		init_flags(va_list ap, const char *format, t_flags *fl, int i)
{
	int j;
	int a;

	fl->prec = -1;
	j = 0;
	a = 0;
	while (check_type(format, fl, i) == -1)
	{
		a = search_flag(ap, format, fl, i);
		j = j + a;
		i = i + a;
		if (check_type(format, fl, i) == -1)
			if (search_flag(ap, format, fl, i) == 0)
				i++;
		a = 0;
	}
	if (check_type(format, fl, i) != -1)
		j = j + check_type(format, fl, i);
	return (j);
}
