/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numbere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:11:59 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:11:23 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_e_nomin(t_flags *fl, t_line *li, char *str, int neg)
{
	int		nbr;

	nbr = ft_strlen(str);
	if ((fl->plus == 1 && neg == 0) ||
	(fl->space == 1 && fl->plus == 0 && neg == 0))
		fl->field_size--;
	if (neg == 1)
		nbr++;
	if (fl->zero == 1)
		while (fl->field_size > nbr)
		{
			str = ft_free_njoin((char*[]){"0", str}, 2, (int[]){0, 1});
			fl->field_size--;
		}
	if (neg == 1)
		str = ft_free_njoin((char*[]){"-", str}, 2, (int[]){0, 1});
	if (fl->plus == 1 && neg == 0)
		str = ft_free_njoin((char*[]){"+", str}, 2, (int[]){0, 1});
	if (fl->space == 1 && fl->plus == 0 && neg == 0)
		str = ft_free_njoin((char*[]){" ", str}, 2, (int[]){0, 1});
	if (fl->zero == 0)
		while (--fl->field_size > nbr - 1)
			str = ft_free_njoin((char*[]){" ", str}, 2, (int[]){0, 1});
	buff_join(str, &li->b);
}

static void	print_e_min(t_flags *fl, t_line *li, char *str, int neg)
{
	int nbr;

	nbr = ft_strlen(str);
	if (neg == 1)
		str = ft_strjoin("-", str);
	if (fl->plus == 1 && neg == 0)
	{
		str = ft_strjoin("+", str);
		fl->field_size--;
	}
	if (fl->space == 1 && fl->plus == 0 && neg == 0)
	{
		str = ft_strjoin(" ", str);
		fl->field_size--;
	}
	buff_join(str, &li->b);
	while (fl->field_size > nbr)
	{
		buff_join(" ", &li->b);
		nbr++;
	}
}

static void	print_e_end(t_flags *fl, t_line *li, char *str, int neg)
{
	if (fl->prec == 0 && fl->sharp == 1)
		str = ft_strjoin(str, ".");
	str = (li->x == 1) ? ft_strjoin(str, "E+")
			: ft_strjoin(str, "e+");
	if (li->power > -10 && li->power < 10)
		str = ft_strjoin(str, "0");
	str = ft_strjoin(str,
	ft_itoa_base((unsigned long int)li->power, li->base));
	if (fl->min == 1)
		print_e_min(fl, li, str, neg);
	else if (fl->min == 0)
		print_e_nomin(fl, li, str, neg);
}

static char	*print_e_prec(t_line *li, long double c, char *str)
{
	int nbr;

	nbr = 0;
	str = print_f_prec(li, nbr, c, str);
	if (str[1] != '.' && str[2] == '.')
	{
		str[2] = str[1];
		str[1] = '.';
		str = ft_strsub(str, 0, ft_strlen(str) - 1);
		li->power++;
	}
	return (str);
}

void		print_numbere(t_flags *fl, t_line *li, long double c)
{
	int		nbr;
	int		neg;
	char	*str;

	str = ft_strnew(0);
	neg = (c < 0) ? 1 : 0;
	begin_e(fl, li, &nbr, &c);
	if (fl->prec == 0)
	{
		print_fzeprec(li, &nbr, &c, &str);
		if (str[1] != '\0')
		{
			str = ft_strsub(str, 0, 1);
			li->power++;
		}
	}
	li->prec = fl->prec;
	if (fl->prec != 0)
		str = print_e_prec(li, c, str);
	fl->prec = li->prec;
	print_e_end(fl, li, str, neg);
}
