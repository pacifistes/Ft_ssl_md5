/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_subkeys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:36:28 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/17 16:16:21 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	left_rotate(uint64_t value, int shift, int size_value)
{
	uint64_t result;

	result = (((value << (64 - size_value + shift)) >> (64 - size_value))
	| (value >> (size_value - shift)));
	return (result);
}

void		create_subkeys(uint64_t *subkeys, uint64_t p_key)
{
	uint64_t	c;
	uint64_t	d;
	int			shift;
	int			i;

	i = 0;
	c = p_key >> 28;
	d = bit_extractor(p_key, 28, 0);
	while (i < 16)
	{
		shift = (i < 2 || i == 8 || i == 15) ? 1 : 2;
		c = left_rotate(c, shift, 28);
		d = left_rotate(d, shift, 28);
		subkeys[i] = permute((c << 28) | d, 56, 48, SUBKEY_PERMUTE);
		i++;
	}
}
