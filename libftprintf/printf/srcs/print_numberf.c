/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numberf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:11:44 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:11:15 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_f_nomin(t_flags *fl, t_line *li, char **str, int *neg)
{
	int nbr;

	nbr = ft_strlen(*str);
	if ((fl->plus == 1 && *neg == 0) ||
	(fl->space == 1 && fl->plus == 0 && *neg == 0))
		fl->field_size--;
	nbr = (fl->prec == 0 && fl->sharp == 1) ? nbr++ : nbr;
	nbr = (*neg == 1) ? nbr++ : nbr;
	if (fl->zero == 1)
		while (fl->field_size-- > nbr)
			*str = ft_strjoin("0", *str);
	*str = (*neg == 1) ? ft_strjoin("-", *str) : *str;
	*str = (fl->plus == 1 && *neg == 0) ? ft_strjoin("+", *str)
	: *str;
	if (fl->space == 1 && fl->plus == 0 && *neg == 0)
		*str = ft_strjoin(" ", *str);
	if (fl->zero == 0)
		while (fl->field_size > nbr)
		{
			*str = ft_strjoin(" ", *str);
			fl->field_size--;
		}
	buff_join(*str, &li->b);
	if (fl->prec == 0 && fl->sharp == 1)
		buff_join(".", &li->b);
}

static void	print_f_min(t_flags *fl, t_line *li, char **str, int *neg)
{
	int nbr;

	nbr = ft_strlen(*str);
	if (*neg == 1)
		*str = (*neg == 1) ? ft_strjoin("-", *str) : *str;
	if (fl->plus == 1 && *neg == 0)
	{
		*str = ft_strjoin("+", *str);
		fl->field_size--;
	}
	if (fl->space == 1 && fl->plus == 0 && *neg == 0)
	{
		*str = ft_strjoin(" ", *str);
		fl->field_size--;
	}
	buff_join(*str, &li->b);
	if (fl->prec == 0 && fl->sharp == 1)
	{
		buff_join(".", &li->b);
		nbr++;
	}
	while (fl->field_size > nbr && ++nbr)
		buff_join(" ", &li->b);
}

void		print_fzeprec(t_line *li, int *nbr, long double *c, char **str)
{
	*c = *c * 100;
	if ((unsigned long int)*c % 10 >= 5 && ((unsigned long int)*c % 10 == 9
	|| (unsigned long int)*c % 100 >= 90))
	{
		*c = *c / 10;
		*str = ft_strjoin(*str,
		ft_itoa_base((unsigned long int)*c, li->base));
		*nbr = ft_strlen(*str) - 1;
		while ((*str[*nbr] == '9' || *str[*nbr] == '.') && *nbr >= 0)
		{
			if (*str[*nbr] == '9')
				*str[*nbr] = '0';
			(*nbr)--;
		}
		if (*nbr == -1)
			*str = ft_strjoin("1", *str);
		else
			*str[*nbr] = *str[*nbr] + 1;
	}
	else
	{
		*c = (((unsigned long int)*c % 10) >= 5) ? (*c + 10) / 10 : *c / 10;
		*str = ft_strjoin(*str,
		ft_itoa_base((unsigned long int)*c, li->base));
	}
}

static void	begin_f(t_line *li, int *nbr, long double *c, char **str)
{
	li->base = 10;
	*c = *c / 10;
	if (*c < 0)
		*c = -(*c);
	while (*c != 0 && *c > 4294967295)
	{
		*c = *c / 10;
		(*nbr)++;
	}
	while (*c != 0 && *nbr != 1)
	{
		while (*c != 0 && *nbr != 1 && *c < 429496728)
		{
			*c = *c * 10;
			(*nbr)--;
		}
		*str = ft_strjoin(*str,
		ft_itoa_base((unsigned long int)*c, li->base));
		*c = *c - (unsigned long int)*c;
	}
}

void		print_numberf(t_flags *fl, t_line *li, long double c)
{
	int		nbr;
	int		neg;
	char	*str;

	neg = (c < 0) ? 1 : 0;
	nbr = 1;
	str = ft_strnew(0);
	begin_f(li, &nbr, &c, &str);
	fl->prec = (fl->prec == -1) ? 6 : fl->prec;
	if (fl->prec == 0)
		print_fzeprec(li, &nbr, &c, &str);
	li->prec = fl->prec;
	if (li->prec != 0)
		str = print_f_prec(li, nbr - 1, c * 10, str);
	fl->prec = li->prec;
	if (fl->min == 1)
		print_f_min(fl, li, &str, &neg);
	else if (fl->min == 0)
		print_f_nomin(fl, li, &str, &neg);
}
