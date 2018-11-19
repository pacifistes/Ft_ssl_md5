/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_e.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 19:15:21 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 19:15:41 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	begin_e(t_flags *fl, t_line *li, int *nbr, long double *c)
{
	li->base = 10;
	*c = *c / 10;
	*nbr = (*c == 0) ? 0 : 1;
	li->x = (fl->type == 'E' || fl->type == 'G') ? 1 : 0;
	if (*c < 0)
		*c = -(*c);
	while (*c >= 10)
	{
		*c = *c / 10;
		(*nbr)++;
	}
	while (*c != 0 && *c < 1)
	{
		*c = *c * 10;
		(*nbr)--;
	}
	if (fl->prec == -1)
		fl->prec = 6;
	li->power = *nbr;
}
