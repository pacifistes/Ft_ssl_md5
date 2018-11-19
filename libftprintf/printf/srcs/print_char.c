/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:05:35 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 14:05:37 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_charmin(t_flags *fl, t_line *li)
{
	while (fl->field_size > 1)
	{
		if (fl->zero == 1)
			buff_join("0", &li->b);
		else
			buff_join(" ", &li->b);
		fl->field_size--;
	}
}

static void	printchar(va_list ap, t_flags *fl, t_line *li)
{
	char *c;

	c = (char*)malloc(sizeof(char) * 2);
	if (!c)
		return ;
	c[0] = va_arg(ap, int);
	c[1] = '\0';
	if (fl->min == 0)
		print_charmin(fl, li);
	if (c[0] != 0)
		buff_join(c, &li->b);
	else
		buff_join_char(0, &li->b);
	if (fl->min == 1)
	{
		while (fl->field_size > 1)
		{
			buff_join(" ", &li->b);
			fl->field_size--;
		}
	}
}

static void	printwchar(va_list ap, t_flags *fl, t_line *li)
{
	unsigned int	nbr;
	char			*str;

	li->ret = 0;
	nbr = va_arg(ap, wchar_t);
	if ((nbr > 55295 && nbr < 57344) || nbr > 1114111)
	{
		li->ret = -1;
		return ;
	}
	if (fl->min == 0)
		print_charmin(fl, li);
	if (nbr == 0)
		buff_join_char(0, &li->b);
	else
	{
		str = ft_convwchar(nbr);
		buff_join(str, &li->b);
		free(str);
	}
	if (fl->min == 1)
		while (--fl->field_size > 0)
			buff_join(" ", &li->b);
}

void		printf_char(va_list ap, t_flags *fl, t_line *li)
{
	if ((fl->type == 'c' && fl->type_var1 == 'l') || fl->type == 'C')
		printwchar(ap, fl, li);
	else
		printchar(ap, fl, li);
}
