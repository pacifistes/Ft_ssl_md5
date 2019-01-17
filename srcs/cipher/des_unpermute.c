/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_unpermute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:31:03 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 22:41:09 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	unpermute(uint64_t value, int size, t_permute_type type)
{
	uint64_t	result;
	int			i;

	result = 0;
	i = -1;
	while (++i < size)
	{
		result |= (((value >> (size - (i + 1))) & 1)
		<< (size - (g_tab_permute[type][i])));
	}
	return (result);
}

uint64_t	unpermute_subkeys(uint64_t reverse, uint64_t *subkeys)
{
	uint32_t	left;
	uint32_t	right;
	uint32_t	right_tmp;
	int			i;

	i = 14;
	right = (reverse >> 32);
	left = (reverse & ((1UL << 32) - 1));
	while (i >= 0)
	{
		right_tmp = right;
		right = left;
		left = (right_tmp ^ f(right, subkeys[i + 1]));
		i--;
	}
	return (((uint64_t)(right ^ f(left, subkeys[0])) << 32) | left);
}
