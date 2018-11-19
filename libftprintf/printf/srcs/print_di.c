/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:16:47 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/24 14:19:09 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	size_nbr(long long int n)
{
	int i;

	i = 0;
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
	return (i);
}

static void	print_this(t_flags *fl, t_line *li, long long int c)
{
	if (fl->plus == 1 && c >= 0)
		fl->field_size--;
	if (fl->min == 1 && fl->plus == 1 && c >= 0)
		buff_join("+", &li->b);
	while (fl->field_size > 0)
	{
		buff_join(" ", &li->b);
		fl->field_size--;
	}
	if (fl->min == 0 && fl->plus == 1 && c >= 0)
		buff_join("+", &li->b);
}

void		printnumber(t_flags *fl, t_line *li, long long int c)
{
	int nbr[2];

	nbr[0] = size_nbr(c);
	nbr[1] = (c == (-9223372036854775807 - 1)) ? 1 : 0;
	if (fl->prec == 0 && c == 0)
		print_this(fl, li, c);
	else if (fl->field_size == -1)
		print_withnofld(fl, li, c, nbr);
	else if (fl->min == 1)
	{
		print_withminbegin(fl, li, c);
		print_withmin(fl, li, c, nbr);
	}
	else if (fl->min == 0)
	{
		printnominbgn(fl, li, c, nbr);
		print_withnomin(fl, li, c, nbr);
	}
}

void		printf_di(va_list ap, t_flags *fl, t_line *li)
{
	long long int c;

	if (fl->type_var1 == 'z')
		c = va_arg(ap, size_t);
	else if (fl->type_var1 == 'j')
		c = va_arg(ap, intmax_t);
	else if (fl->type_var1 == 'l' && fl->type_var2 == '\0')
		c = va_arg(ap, long int);
	else if (fl->type_var1 == 'l' && fl->type_var2 == 'l')
		c = va_arg(ap, long long int);
	else if (fl->type == 'D')
		c = va_arg(ap, long int);
	else
	{
		if (fl->type_var1 == 'h' && fl->type_var2 == '\0')
			c = (short)va_arg(ap, int);
		else if (fl->type_var1 == 'h' && fl->type_var2 == 'h')
			c = (signed char)va_arg(ap, int);
		else
			c = va_arg(ap, int);
	}
	printnumber(fl, li, c);
}
