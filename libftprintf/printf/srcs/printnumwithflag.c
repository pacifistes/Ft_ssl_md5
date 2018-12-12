/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnumwithflag.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:22:25 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/11 22:47:14 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_withnofld(t_flags *fl, t_line *li, long long int c, int *nbr)
{
	char *str;

	if (fl->space == 1 && fl->plus == 0 && c >= 0)
		buff_join(" ", &li->b);
	if (fl->plus == 1 && c >= 0)
		buff_join("+", &li->b);
	if (c < 0 && nbr[1] == 0)
	{
		buff_join("-", &li->b);
		c = -c;
		nbr[0]--;
	}
	while (fl->prec > nbr[0])
	{
		buff_join("0", &li->b);
		fl->prec--;
	}
	str = ft_itoll(c);
	if (str)
	{
		buff_join(str, &li->b);
		free(str);
	}
}

void		print_withminbegin(t_flags *fl, t_line *li, long long int c)
{
	if (fl->space == 1 && fl->plus == 0 && c >= 0)
	{
		buff_join(" ", &li->b);
		fl->field_size--;
	}
}

void		print_withmin(t_flags *fl, t_line *li, long long int c, int *nbr)
{
	char *str;

	if (fl->plus == 1 && c >= 0)
	{
		buff_join("+", &li->b);
		fl->field_size--;
	}
	fl->prec = (fl->prec >= nbr[0] && c < 0) ? fl->prec + 1 : fl->prec;
	if (c < 0 && nbr[1] == 0)
		buff_join("-", &li->b);
	c = (c < 0 && nbr[1] == 0) ? -c : c;
	while (fl->prec > nbr[0])
	{
		buff_join("0", &li->b);
		nbr[0]++;
	}
	str = ft_itoll(c);
	buff_join(str, &li->b);
	free(str);
	while (fl->field_size > nbr[0])
	{
		buff_join(" ", &li->b);
		nbr[0]++;
	}
}

void		printnominbgn(t_flags *fl, t_line *li, long long int c, int *nbr)
{
	if ((fl->plus == 1 && c >= 0) ||
	(fl->space == 1 && fl->plus == 0 && c >= 0) || (
	fl->prec >= nbr[0] && c < 0))
		fl->field_size--;
	if ((fl->zero == 0 && fl->prec <= nbr[0]) || (fl->zero == 1
	&& fl->prec <= nbr[0] && fl->prec >= 0))
		while (fl->field_size > nbr[0])
		{
			buff_join(" ", &li->b);
			fl->field_size--;
		}
	else if (fl->prec > nbr[0] && fl->prec < fl->field_size)
		while (fl->field_size > fl->prec)
		{
			buff_join(" ", &li->b);
			fl->field_size--;
		}
	if (fl->space == 1 && fl->plus == 0 && c >= 0)
		buff_join(" ", &li->b);
	if (fl->plus == 1 && c >= 0)
		buff_join("+", &li->b);
}

void		print_withnomin(t_flags *fl, t_line *li, long long int c, int *nbr)
{
	char *str;

	if (c < 0 && nbr[1] == 0)
	{
		buff_join("-", &li->b);
		c = -c;
		nbr[0]--;
		fl->field_size--;
	}
	while (fl->field_size > nbr[0] || fl->prec > nbr[0])
	{
		buff_join("0", &li->b);
		fl->field_size--;
		fl->prec--;
	}
	str = ft_itoll(c);
	if (str)
	{
		buff_join(str, &li->b);
		free(str);
	}
}
