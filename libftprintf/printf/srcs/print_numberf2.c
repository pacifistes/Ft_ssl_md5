/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_numberf2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:11:22 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 15:10:33 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*print_f_prec_next(t_line *li, int nbr, long double c, char *str)
{
	if ((unsigned long int)c % 10 >= 5 && ((unsigned long int)c % 10 == 9
	|| (unsigned long int)c % 100 >= 90))
	{
		c = c / 10;
		str = ft_strjoin(str, ft_itoa_base((unsigned long int)c, li->base));
		nbr = ft_strlen(str) - 1;
		while ((str[nbr] == '9' || str[nbr] == '.') && nbr >= 0)
			if (str[nbr--] == '9')
				str[nbr + 1] = '0';
		if (nbr == -1)
			str = ft_strjoin("1", str);
		else
			str[nbr] = str[nbr] + 1;
		nbr = li->prec + 1;
	}
	else
	{
		c = (((unsigned long int)c % 10) >= 5) ? (c + 10) / 10 : c / 10;
		str = ft_strjoin(str, ft_itoa_base((unsigned long int)c, li->base));
	}
	return (str);
}

char		*print_f_prec(t_line *li, int nbr, long double c, char *str)
{
	str = ft_strjoin(str, ft_itoa_base((unsigned long int)c, li->base));
	c = c - (unsigned long int)c;
	str = ft_strjoin(str, ".");
	while (c != 0 && nbr < (li->prec + 1) && c < 429496728)
	{
		while (c != 0 && nbr < (li->prec + 1) && c < 429496728)
		{
			c = c * 10;
			nbr++;
		}
		if (nbr == li->prec + 1)
			str = print_f_prec_next(li, nbr, c, str);
		else
		{
			str = ft_strjoin(str,
			ft_itoa_base((unsigned long int)c, li->base));
			c = c - (unsigned long int)c;
		}
	}
	return (str);
}
