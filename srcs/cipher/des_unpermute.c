/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_unpermute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:31:03 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/17 16:15:28 by bbrunell         ###   ########.fr       */
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

void		unpermute_subkeys(t_des *des, uint64_t reverse)
{
	uint64_t	previous_left;
	uint64_t	previous_right;
	int			i;

	i = 14;
	previous_right = (reverse >> 32);
	previous_left = (reverse & ((1UL << 32) - 1));
	while (i >= 0)
	{
		if (i < 14)
		{
			previous_right = des->p_subkey.right[i + 1];
			previous_left = des->p_subkey.left[i + 1];
		}
		des->p_subkey.right[i] = previous_left;
		des->p_subkey.left[i] = (previous_right
		^ f(des->p_subkey.right[i], des->subkey[i + 1]));
		i--;
	}
	des->ip = (((des->p_subkey.right[0]
	^ f(des->p_subkey.left[0], des->subkey[0])) << 32)
	| (des->p_subkey.left[0]));
}
