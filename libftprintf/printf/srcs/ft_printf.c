/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 13:03:15 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/13 13:03:18 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_color(const char *format, t_line *li, int i)
{
	if (ft_strncmp(format + i, "white}", 6) == 0)
	{
		buff_join("\e[0;21m", &li->b);
		return (6);
	}
	else if (ft_strncmp(format + i, "red}", 4) == 0 ||
	ft_strncmp(format + i, "eoc}", 4) == 0)
	{
		(ft_strncmp(format + i, "eoc}", 4) == 0) ?
		buff_join("\e[0;0m", &li->b) :
		buff_join("\e[0;31m", &li->b);
		return (4);
	}
	else if (ft_strncmp(format + i, "green}", 6) == 0)
	{
		buff_join("\e[0;32m", &li->b);
		return (6);
	}
	else if (ft_strncmp(format + i, "blue}", 5) == 0)
	{
		buff_join("\e[0;34m", &li->b);
		return (5);
	}
	buff_join("{", &li->b);
	return (0);
}

static void	ft_parse_printf(va_list ap, const char *format, t_line *li)
{
	int		i;
	int		j;

	i = 0;
	while (format[i] != '\0')
	{
		j = i;
		while (format[i] != '%' && format[i] != '{' && format[i] != '\0')
			i++;
		if (i - j > 0)
		{
			buff_sub_join(format, &li->b, j, i - j);
		}
		j = i;
		j++;
		if (format[i] == '{')
			i = i + ft_color(format, li, j);
		else if (format[i] == '%')
			i = i + ft_init(ap, format, li, j);
		if (format[i] == '\0')
			return ;
		i++;
	}
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	t_line	li;

	li.ret = 0;
	li.b.buff = 0;
	li.b.nbr_write = 0;
	if (ft_error(&format) == 1)
	{
		va_start(ap, format);
		ft_parse_printf(ap, format, &li);
	}
	if (li.ret == -1)
		return (-1);
	li.b.nbr_write = li.b.nbr_write * BUFFER + li.b.buff;
	write(1, li.b.str_buff, li.b.buff);
	va_end(ap);
	return (li.b.nbr_write);
}
