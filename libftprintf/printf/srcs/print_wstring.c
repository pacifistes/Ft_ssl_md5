/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wstring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/07 08:54:55 by bbrunell          #+#    #+#             */
/*   Updated: 2016/06/07 08:54:58 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printprec(t_flags *fl, t_line *li, wchar_t *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (fl->prec >= ft_wstrlen(str[i]))
	{
		tmp = ft_convwchar(str[i]);
		buff_join(tmp, &li->b);
		fl->prec = fl->prec - ft_wstrlen(str[i]);
		free(tmp);
		i++;
	}
}

static void	printnominwstring(t_flags *fl, t_line *li, int nbr, wchar_t *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (fl->field_size > nbr)
	{
		if (fl->zero == 0)
			buff_join(" ", &li->b);
		else
			buff_join("0", &li->b);
		nbr++;
	}
	if (fl->prec >= 0)
		printprec(fl, li, str);
	else
		while (str[i])
		{
			tmp = ft_convwchar(str[i]);
			buff_join(tmp, &li->b);
			free(tmp);
			i++;
		}
}

static void	printminwstring(t_flags *fl, t_line *li, int nbr, wchar_t *str)
{
	int		i;
	char	*tmp;

	i = 0;
	if (fl->prec >= 0)
		printprec(fl, li, str);
	else
	{
		while (str[i])
		{
			tmp = ft_convwchar(str[i]);
			buff_join(tmp, &li->b);
			free(tmp);
			i++;
		}
	}
	while (fl->field_size > nbr)
	{
		buff_join(" ", &li->b);
		nbr++;
	}
}

static int	find_nbr(t_flags *fl, int nbr, wchar_t *str)
{
	int	i;
	int prec;

	i = 0;
	prec = fl->prec;
	while (prec >= ft_wstrlen(str[i]))
	{
		prec = prec - ft_wstrlen(str[i]);
		i++;
	}
	if (str[i] && prec < ft_wstrlen(str[i]))
		while (str[i])
		{
			nbr = nbr - ft_wstrlen(str[i]);
			i++;
		}
	return (nbr);
}

void		printwstring(va_list ap, t_flags *fl, t_line *li)
{
	wchar_t	*str;
	int		nbr;
	int		i;

	str = va_arg(ap, wchar_t*);
	i = 0;
	nbr = 0;
	if (str == 0)
	{
		printstring(ap, fl, li);
		return ;
	}
	while (str[i])
	{
		nbr = nbr + ft_wstrlen(str[i]);
		i++;
	}
	if (fl->prec >= 0)
		nbr = find_nbr(fl, nbr, str);
	if (fl->min == 1)
		printminwstring(fl, li, nbr, str);
	if (fl->min == 0)
		printnominwstring(fl, li, nbr, str);
}
