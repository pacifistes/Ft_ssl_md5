/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 12:47:14 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/24 12:47:18 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_type(const char *format, t_flags *fl, int i)
{
	if (format[i] == 's' || format[i] == 'S' || format[i] == 'p' ||
		format[i] == 'd' || format[i] == 'D' || format[i] == 'i' ||
		format[i] == 'o' || format[i] == 'O' || format[i] == 'u' ||
		format[i] == 'U' || format[i] == 'x' || format[i] == 'X' ||
		format[i] == 'c' || format[i] == 'C' || format[i] == '%' ||
		format[i] == 't' || format[i] == 'T' || format[i] == 'w' ||
		format[i] == 'b' || format[i] == 'B' || format[i] == 'f' ||
		format[i] == 'F' || format[i] == 'm' || format[i] == 'M' ||
		format[i] == 'e' || format[i] == 'E' || format[i] == 'g' ||
		format[i] == 'G')
	{
		fl->type = format[i];
		return (1);
	}
	else if ((format[i] >= 'A' && format[i] <= 'Z' && format[i] != 'L') ||
	(format[i] >= 'a' && format[i] <= 'z' && format[i] != 'j' &&
	format[i] != 'l' && format[i] != 'z' && format[i] != 'h'))
	{
		fl->type = format[i];
		return (1);
	}
	if (format[i] == '\0')
		return (0);
	return (-1);
}
