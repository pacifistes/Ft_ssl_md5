/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:20:30 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 12:20:37 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	search_type_var(const char *format, t_flags *fl, int i)
{
	int j;

	j = 0;
	if (format[i] == 'h' || format[i] == 'l' || format[i] == 'j' ||
		format[i] == 'z' || format[i] == 'L')
	{
		fl->type_var1 = format[i];
		i++;
		j++;
		if (format[i] == 'h' || format[i] == 'l')
		{
			fl->type_var2 = format[i];
			j++;
			i++;
		}
	}
	return (j);
}

static int	search_prec(va_list ap, const char *format, t_flags *fl, int i)
{
	int j;
	int nbr;

	j = i;
	nbr = 0;
	if (format[i] == '.')
	{
		i = (format[i + 1] == '*') ? i + 2 : i + 1;
		if (format[i - 1] == '*')
		{
			fl->prec = va_arg(ap, int);
			fl->prec = (fl->prec < 0) ? -1 : fl->prec;
		}
		else
		{
			while (ft_isdigit(format[i]) == 1)
			{
				nbr = nbr * 10 + format[i] - 48;
				i++;
			}
			fl->prec = nbr;
		}
	}
	j = i - j;
	return (j + search_type_var(format, fl, i));
}

static void	field_sizeend(va_list ap, const char *format, t_flags *fl, int *i)
{
	if (format[*i] == '*')
	{
		fl->field_size = va_arg(ap, int);
		if (fl->field_size < 0)
		{
			fl->min = 1;
			fl->field_size = -fl->field_size;
		}
		(*i)++;
	}
}

static int	search_fieldsize(va_list ap, const char *format, t_flags *fl, int i)
{
	int j;
	int nbr;

	j = i;
	nbr = 0;
	if (ft_isdigit(format[i]) == 1 || format[i] == '*')
	{
		while (ft_isdigit(format[i]) == 1 || format[i] == '*')
		{
			while (ft_isdigit(format[i]) == 1)
			{
				nbr = nbr * 10 + format[i] - 48;
				i++;
			}
			fl->field_size = nbr;
			field_sizeend(ap, format, fl, &i);
		}
	}
	j = i - j;
	if (fl->field_size == 0)
		fl->field_size = -1;
	return (j + search_prec(ap, format, fl, i));
}

int			search_flag(va_list ap, const char *format, t_flags *fl, int i)
{
	int j;

	j = 0;
	while (format[i] == '#' || format[i] == '+' || format[i] == '0' ||
	format[i] == '-' || format[i] == ' ')
	{
		fl->sharp = (format[i] == '#') ? 1 : fl->sharp;
		fl->min = (format[i] == '-') ? 1 : fl->min;
		fl->plus = (format[i] == '+') ? 1 : fl->plus;
		fl->zero = (format[i] == '0') ? 1 : fl->zero;
		fl->space = (format[i] == ' ') ? 1 : fl->space;
		i++;
		j++;
	}
	return (j + search_fieldsize(ap, format, fl, i));
}
