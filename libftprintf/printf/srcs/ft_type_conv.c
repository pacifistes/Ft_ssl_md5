/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:37:20 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/24 12:37:22 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_type_conv_end(t_flags *fl, va_list ap, t_line *li)
{
	if (fl->type == 'w')
		printf_w(ap, fl, li);
	else if (fl->type == 'b' || fl->type == 'B')
		printf_b(ap, fl, li);
	else if (fl->type == 'f' || fl->type == 'F')
		printf_f(ap, fl, li);
	else if (fl->type == 'e' || fl->type == 'E')
		printf_e(ap, fl, li);
	else if (fl->type == 'm' || fl->type == 'M')
		printf_m(ap, fl, li);
	else if (fl->type == 'g' || fl->type == 'G')
		printf_g(ap, fl, li);
	else if (fl->type != '\0')
		printf_void(fl, li);
}

void	ft_type_conv(t_flags *fl, va_list ap, t_line *li)
{
	li->ret = 0;
	if (fl->type == '%')
		printf_percent(fl, li);
	else if (fl->type == 's' || fl->type == 'S')
		printf_str(ap, fl, li);
	else if (fl->type == 'c' || fl->type == 'C')
		printf_char(ap, fl, li);
	else if (fl->type == 'd' || fl->type == 'i' || fl->type == 'D')
		printf_di(ap, fl, li);
	else if (fl->type == 'p')
		printf_p(ap, fl, li);
	else if (fl->type == 'x' || fl->type == 'X')
		printf_x(ap, fl, li);
	else if (fl->type == 'o' || fl->type == 'O')
		printf_o(ap, fl, li);
	else if (fl->type == 'u' || fl->type == 'U')
		printf_u(ap, fl, li);
	else if (fl->type == 't')
		printf_t(ap, fl, li, (va_arg(ap, int)));
	else if (fl->type == 'T')
		printf_majt(ap, fl, li);
	else
		ft_type_conv_end(fl, ap, li);
}
