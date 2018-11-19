/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:09:25 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 14:09:27 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printnominstring(t_flags *fl, t_line *li, int nbr, char *str)
{
	if (fl->prec >= 0)
		while (fl->prec < nbr)
			nbr--;
	while (fl->field_size > nbr)
	{
		if (fl->zero == 0)
			buff_join(" ", &li->b);
		else
			buff_join("0", &li->b);
		nbr++;
	}
	if (fl->prec >= 0)
		buff_sub_join(str, &li->b, 0, fl->prec);
	else
		buff_join(str, &li->b);
}

void		printstring(va_list ap, t_flags *fl, t_line *li)
{
	char	*str;
	int		nbr;

	str = (fl->type == 's') ? va_arg(ap, char *) : "(null)";
	if (str == 0)
		str = "(null)";
	nbr = ft_strlen(str);
	if (fl->min == 1)
	{
		if (fl->prec >= 0)
			while (fl->prec < nbr)
				nbr--;
		if (fl->prec >= 0)
			buff_sub_join(str, &li->b, 0, fl->prec);
		else
			buff_join(str, &li->b);
		while (fl->field_size > nbr)
		{
			buff_join(" ", &li->b);
			nbr++;
		}
	}
	if (fl->min == 0)
		printnominstring(fl, li, nbr, str);
}

void		printf_str(va_list ap, t_flags *fl, t_line *li)
{
	if ((fl->type == 's' && fl->type_var1 == 'l') || fl->type == 'S')
		printwstring(ap, fl, li);
	else
		printstring(ap, fl, li);
}
