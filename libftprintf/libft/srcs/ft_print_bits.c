/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:17:11 by bbrunell          #+#    #+#             */
/*   Updated: 2015/11/30 11:29:14 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_bits(unsigned char octet)
{
	int nbr;

	nbr = 128;
	while (nbr > 0)
	{
		if (nbr <= octet)
		{
			write(1, "1", 1);
			octet = octet - nbr;
		}
		else
			write(1, "0", 1);
		nbr = nbr / 2;
	}
	write(1, "\n", 1);
}
