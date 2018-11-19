/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:29:16 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 12:29:22 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		printf_o(va_list ap, t_flags *fl, t_line *li)
{
	unsigned long long int c;

	if (fl->type_var1 == 'z')
		c = va_arg(ap, size_t);
	else if (fl->type_var1 == 'j')
		c = va_arg(ap, uintmax_t);
	else if (fl->type_var1 == 'l' && fl->type_var2 == '\0')
		c = va_arg(ap, unsigned long int);
	else if (fl->type_var1 == 'l' && fl->type_var2 == 'l')
		c = va_arg(ap, unsigned long long int);
	else if (fl->type == 'O')
		c = va_arg(ap, unsigned long int);
	else
	{
		if (fl->type_var1 == 'h' && fl->type_var2 == '\0')
			c = (unsigned short)va_arg(ap, int);
		else if (fl->type_var1 == 'h' && fl->type_var2 == 'h')
			c = (unsigned char)va_arg(ap, int);
		else
			c = va_arg(ap, unsigned int);
	}
	li->base = 8;
	li->x = 0;
	printnum_uox(c, fl, li);
}

void		printf_x(va_list ap, t_flags *fl, t_line *li)
{
	unsigned long long int c;

	if (fl->type_var1 == 'z')
		c = va_arg(ap, size_t);
	else if (fl->type_var1 == 'j')
		c = va_arg(ap, uintmax_t);
	else if (fl->type_var1 == 'l' && fl->type_var2 == 'l')
		c = va_arg(ap, unsigned long long int);
	else if (fl->type_var1 == 'l' && fl->type_var2 == '\0')
		c = va_arg(ap, unsigned long int);
	else
	{
		if (fl->type_var1 == 'h' && fl->type_var2 == '\0')
			c = (unsigned short)va_arg(ap, int);
		else if (fl->type_var1 == 'h' && fl->type_var2 == 'h')
			c = (unsigned char)va_arg(ap, int);
		else
			c = va_arg(ap, unsigned int);
	}
	li->x = (fl->type == 'X') ? 1 : 0;
	li->base = 16;
	printnum_uox(c, fl, li);
}

void		printf_u(va_list ap, t_flags *fl, t_line *li)
{
	unsigned long long int c;

	if (fl->type_var1 == 'z')
		c = va_arg(ap, size_t);
	else if (fl->type_var1 == 'j')
		c = va_arg(ap, uintmax_t);
	else if (fl->type_var1 == 'l' && fl->type_var2 == '\0')
		c = va_arg(ap, unsigned long int);
	else if (fl->type_var1 == 'l' && fl->type_var2 == 'l')
		c = va_arg(ap, unsigned long long int);
	else if (fl->type == 'U')
		c = va_arg(ap, unsigned long int);
	else
	{
		if (fl->type_var1 == 'h' && fl->type_var2 == '\0')
			c = (unsigned short)va_arg(ap, int);
		else if (fl->type_var1 == 'h' && fl->type_var2 == 'h')
			c = (unsigned char)va_arg(ap, int);
		else
			c = va_arg(ap, unsigned int);
	}
	li->base = 10;
	li->x = 0;
	printnum_uox(c, fl, li);
}

void		printf_p(va_list ap, t_flags *fl, t_line *li)
{
	unsigned long long int c;

	c = va_arg(ap, unsigned long long int);
	li->x = 0;
	li->base = 16;
	fl->sharp = 1;
	printnum_uox(c, fl, li);
}

void		printf_b(va_list ap, t_flags *fl, t_line *li)
{
	unsigned long long int c;

	if (fl->type_var1 == 'z')
		c = va_arg(ap, size_t);
	else if (fl->type_var1 == 'j')
		c = va_arg(ap, uintmax_t);
	else if (fl->type_var1 == 'l' && fl->type_var2 == '\0')
		c = va_arg(ap, unsigned long int);
	else if (fl->type_var1 == 'l' && fl->type_var2 == 'l')
		c = va_arg(ap, unsigned long long int);
	else if (fl->type == 'B')
		c = va_arg(ap, unsigned long int);
	else
	{
		if (fl->type_var1 == 'h' && fl->type_var2 == '\0')
			c = (short)va_arg(ap, unsigned int);
		else if (fl->type_var1 == 'h' && fl->type_var2 == 'h')
			c = (char)va_arg(ap, unsigned int);
		else
			c = va_arg(ap, int);
	}
	li->base = 2;
	li->x = 0;
	printnum_uox(c, fl, li);
}
