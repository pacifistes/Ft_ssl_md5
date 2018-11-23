/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printnum_uox.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 14:55:18 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:56:03 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	find_nbzero(t_flags *fl, int *nbr, int sign)
{
	int		nbzero;

	nbzero = 0;
	if (fl->prec > *nbr - sign)
	{
		nbzero += fl->prec - *nbr + sign;
		*nbr += nbzero;
	}
	if (fl->field_size >= 0 && fl->zero == 1 && fl->min == 0 &&
	fl->prec == -1 && fl->field_size > *nbr)
	{
		nbzero += fl->field_size - *nbr;
		*nbr += nbzero;
	}
	return (nbzero);
}

static int	find_nbspaces(t_flags *fl, int *nbr)
{
	int		nbspaces;

	nbspaces = 0;
	if (fl->field_size >= 0 && (fl->zero == 0 || fl->min == 1 || fl->prec >= 0)
		&& fl->field_size > *nbr)
	{
		nbspaces += fl->field_size - *nbr;
		*nbr += nbspaces;
	}
	return (nbspaces);
}

static int	begin(unsigned long long int c, t_flags *fl, t_line *li, int sign)
{
	if (((li->base == 8 && fl->sharp == 1) && (c != 0 || (c == 0 &&
	fl->prec == 0))) || (li->base == 16 && fl->type != 'p' && fl->sharp == 1 &&
	c != 0) || fl->type == 'p')
		sign = (li->base == 16) ? 2 : 1;
	return (sign);
}

static void	middle(t_flags *fl, t_line *li, int nbspaces, int n)
{
	if (fl->min == 0 && n == 0)
		while (nbspaces > 0)
		{
			buff_join(" ", &li->b);
			nbspaces--;
		}
	if (fl->min == 1 && n == 1)
		while (nbspaces > 0)
		{
			buff_join(" ", &li->b);
			nbspaces--;
		}
}

/*
** n.nbr
** n.sigh 2 == base 16 | base 8
**	n.nbzero
*/

void		printnum_uox(unsigned long long int c, t_flags *fl, t_line *li)
{
	t_num_uox	n;
	char		*str;

	n.nbr = (c == 0 && fl->prec == 0) ? 0 : base_len(c, li->base);
	n.sign = 0;
	n.sign = begin(c, fl, li, n.sign);
	n.nbr = n.nbr + n.sign;
	n.nbzero = find_nbzero(fl, &n.nbr, (n.sign == 2) ? 2 : 0);
	n.nbspaces = find_nbspaces(fl, &n.nbr);
	middle(fl, li, n.nbspaces, 0);
	if (n.sign == 1)
		buff_join("0", &li->b);
	else if (n.sign == 2)
		(li->x == 0) ? buff_join("0x", &li->b)
		: buff_join("0X", &li->b);
	while (--n.nbzero > -1)
		buff_join("0", &li->b);
	if (!(fl->prec == 0 && c == 0))
	{
		str = ft_itoa_base(c, li->base);
		buff_join(str, &li->b);
		free(str);
	}
	middle(fl, li, n.nbspaces, 1);
}
