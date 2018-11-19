/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 12:35:33 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/26 12:35:38 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_voidmin(t_flags *fl, t_line *li, char **c, int *i)
{
	while (fl->field_size > *i)
	{
		if (fl->zero == 1)
			buff_join("0", &li->b);
		else
			buff_join(" ", &li->b);
		fl->field_size--;
	}
	buff_join(*c, &li->b);
}

void		printf_void(t_flags *fl, t_line *li)
{
	int		i;
	char	*c;

	c = (char*)malloc(sizeof(char) * 2);
	if (!c)
		return ;
	c[0] = fl->type;
	c[1] = '\0';
	i = 1;
	if (fl->min == 1)
	{
		buff_join(c, &li->b);
		while (fl->field_size > i)
		{
			buff_join(" ", &li->b);
			fl->field_size--;
		}
	}
	else if (fl->min == 0)
		print_voidmin(fl, li, &c, &i);
}

void		printf_t(va_list ap, t_flags *fl, t_line *li, int nbr)
{
	int *c;
	int i;

	c = va_arg(ap, int*);
	i = 0;
	while (nbr > 0)
	{
		buff_join("[", &li->b);
		printnumber(fl, li, c[i]);
		buff_join("] ", &li->b);
		nbr--;
		i++;
	}
}

void		printf_majt(va_list ap, t_flags *fl, t_line *li)
{
	int x;
	int y;
	int i;
	int j;
	int **c;

	y = va_arg(ap, int);
	x = va_arg(ap, int);
	i = 0;
	j = 0;
	c = va_arg(ap, int**);
	while (j < y)
	{
		while (i < x)
		{
			buff_join("[", &li->b);
			printnumber(fl, li, c[j][i]);
			buff_join("] ", &li->b);
			i++;
		}
		buff_join("\n", &li->b);
		i = 0;
		j++;
	}
}
