/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_percent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 13:37:59 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 13:38:02 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printf_percent(t_flags *fl, t_line *li)
{
	int i;

	i = 0;
	if (fl->field_size == -1)
		buff_join("%", &li->b);
	else
	{
		if (fl->min == 1)
			buff_join("%", &li->b);
		while (i < fl->field_size - 1)
		{
			if (fl->min == 1 || fl->zero == 0)
				buff_join(" ", &li->b);
			else
				buff_join("0", &li->b);
			i++;
		}
		if (fl->min == 0)
			buff_join("%", &li->b);
	}
}
