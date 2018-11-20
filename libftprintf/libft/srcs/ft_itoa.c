/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 12:34:50 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/29 10:25:12 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_itoa_nbr(int n)
{
	int i;

	i = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 9)
	{
		i++;
		n = n / 10;
	}
	i++;
	return (i);
}

static char	*ft_itoa_suite(char *nbr, int n, int size_n)
{
	if (n < 0)
	{
		nbr[0] = '-';
		n = -n;
	}
	size_n--;
	while (n > 9)
	{
		nbr[size_n] = (n % 10) + 48;
		n = n - (n % 10);
		n = n / 10;
		size_n--;
	}
	if (n < 10)
	{
		nbr[size_n] = n + 48;
		size_n--;
	}
	return (nbr);
}

char		*ft_itoa(int n)
{
	int		size_n;
	char	*nbr;

	size_n = ft_itoa_nbr(n);
	nbr = (size_n == 11) ? NULL : ft_strnew(size_n);
	if (nbr == NULL || size_n == 11)
		return ((size_n != 11) ? NULL : ft_strdup("-2147483648"));
	if (size_n == 1)
	{
		nbr[0] = n + 48;
		return (nbr);
	}
	if (size_n == 2 && n < 0)
	{
		nbr[0] = '-';
		nbr[1] = n + 48;
		return (nbr);
	}
	else
		return (ft_itoa_suite(nbr, n, size_n));
}
