/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 12:57:15 by bbrunell          #+#    #+#             */
/*   Updated: 2016/05/13 12:57:18 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int		ft_verifint_suite(const char *str, long int i)
{
	int			j;
	long int	nbr;
	long int	coef;

	j = i + 1;
	nbr = 0;
	coef = 1;
	while (str[j] >= '0' && str[j] <= '9')
		j++;
	j--;
	while (j != i)
	{
		nbr = nbr + coef * (str[j] - '0');
		coef = coef * 10;
		j--;
	}
	if (str[j] == '-')
		nbr = -nbr;
	if (str[j] >= '0' && str[j] <= '9')
		nbr = nbr + coef * (str[j] - '0');
	if (nbr >= -2147483648 && nbr <= 2147483647)
		return (nbr);
	return (2147484848);
}

long int			ft_verifint(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\n' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == '\t' || str[i] == '\r'))
		i++;
	if ((str[i] >= '0' && str[i] <= '9') || ((str[i] == '-' || str[i] == '+')
	&& (str[i + 1] >= '0' && str[i + 1] <= '9')))
		return (ft_verifint_suite(str, i));
	return (2147484848);
}
