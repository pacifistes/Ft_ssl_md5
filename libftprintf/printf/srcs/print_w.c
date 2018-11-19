/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_w.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:10:20 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 14:10:21 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_wmin(t_flags *fl, t_line *li, int **nbr, char ***str)
{
	if (fl->prec >= 0)
		while (fl->prec < *nbr[0])
			(*nbr[0])--;
	if (fl->prec >= 0)
		buff_sub_join(*str[*nbr[1]], &li->b, 0, fl->prec);
	else
		buff_join(*str[*nbr[1]], &li->b);
	while (fl->field_size > *nbr[0])
	{
		buff_join(" ", &li->b);
		(*nbr[0])++;
	}
}

static void	print_wnomin(t_flags *fl, t_line *li, int **nbr, char ***str)
{
	if (fl->prec >= 0)
		while (fl->prec < *nbr[0])
			(*nbr[0])--;
	while (fl->field_size > *nbr[0])
	{
		if (fl->zero == 0)
			buff_join(" ", &li->b);
		else
			buff_join("0", &li->b);
		(*nbr[0])++;
	}
	if (fl->prec >= 0)
		buff_sub_join(*str[*nbr[1]], &li->b, 0, fl->prec);
	else
		buff_join(*str[*nbr[1]], &li->b);
}

void		printf_w(va_list ap, t_flags *fl, t_line *li)
{
	char	**str;
	int		*nbr;
	int		x;

	nbr = (int*)malloc(sizeof(int) * 2);
	x = va_arg(ap, int);
	str = va_arg(ap, char**);
	nbr[1] = 0;
	while (nbr[1] < x)
	{
		if (str[nbr[1]] == 0)
			str[nbr[1]] = "(null)";
		nbr[0] = ft_strlen(str[nbr[1]]);
		if (fl->min == 1)
			print_wmin(fl, li, &nbr, &str);
		else if (fl->min == 0)
			print_wnomin(fl, li, &nbr, &str);
		nbr[1]++;
	}
}
