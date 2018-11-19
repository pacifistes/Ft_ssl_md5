/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_efg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 13:35:57 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 13:36:10 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printf_f(va_list ap, t_flags *fl, t_line *li)
{
	long double c;

	if (fl->type_var1 == 'L')
		c = va_arg(ap, long double);
	else
		c = va_arg(ap, double);
	print_numberf(fl, li, c);
}

void		printf_e(va_list ap, t_flags *fl, t_line *li)
{
	long double c;

	if (fl->type_var1 == 'L')
		c = va_arg(ap, long double);
	else
		c = va_arg(ap, double);
	print_numbere(fl, li, c);
}

static void	ft_getpower(long double *c, int *power)
{
	*c = *c / 10;
	if (*c < 0)
		*c = -*c;
	while (*c >= 10)
	{
		*c = *c / 10;
		(*power)++;
	}
	while (*c < 1)
	{
		*c = *c * 10;
		(*power)--;
	}
}

void		printf_g(va_list ap, t_flags *fl, t_line *li)
{
	long double	c;
	int			power;
	long double	d;

	if (fl->type_var1 == 'L')
		c = va_arg(ap, long double);
	else
		c = va_arg(ap, double);
	d = c;
	power = 1;
	ft_getpower(&c, &power);
	if (fl->prec == 0)
		fl->prec = 1;
	if (fl->prec == -1)
		fl->prec = 6;
	if (fl->prec > power && power >= -4)
	{
		fl->prec = fl->prec - (power + 1);
		print_numberf(fl, li, d);
	}
	else
	{
		fl->prec = fl->prec - 1;
		print_numbere(fl, li, d);
	}
}
