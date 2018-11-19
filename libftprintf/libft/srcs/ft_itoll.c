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

static int	ft_itoll_nbr(long long int n)
{
	int i;

	i = 0;
	if (n > (-9223372036854775807 - 1) && n <= 9223372036854775807)
	{
		if (n < 0)
		{
			i++;
			n = -n;
		}
		while (n > 9)
		{
			i++;
			n = n - (n % 10);
			n = n / 10;
		}
		i++;
	}
	if (n == (-9223372036854775807 - 1))
		i = 20;
	return (i);
}

static char	*ft_itoll_suite(char *nbr, long long int n, int size_n)
{
	size_n--;
	if (n < 0)
	{
		nbr[0] = '-';
		n = -n;
	}
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

char		*ft_itoll(long long int n)
{
	int		size_n;
	char	*nbr;

	if (n >= (-9223372036854775807 - 1) && n <= 9223372036854775807)
	{
		size_n = ft_itoll_nbr(n);
		nbr = ft_strnew(size_n);
		if (!nbr || n == (-9223372036854775807 - 1))
			return ((nbr == NULL) ? NULL : ft_strdup("-9223372036854775808"));
		else if (size_n == 1)
		{
			nbr[0] = n + 48;
			return (nbr);
		}
		else if (size_n == 2 && n < 0)
		{
			nbr[0] = '-';
			nbr[1] = -n + 48;
			return (nbr);
		}
		else
			return (ft_itoll_suite(nbr, n, size_n));
	}
	return (NULL);
}
