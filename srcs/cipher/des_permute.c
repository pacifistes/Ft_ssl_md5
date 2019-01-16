/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_permute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:32:02 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 17:45:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	f(uint64_t right, uint64_t key)
{
	uint64_t	new_right;
	uint64_t	result;
	uint8_t		block;
	int			i;

	new_right = permute(right, 32, 48, E_PERMUTE) ^ key;
	i = 0;
	result = 0;
	while (i < 8)
	{
		block = bit_extractor(new_right, 6, 48 - ((i + 1) * 6));
		result |= g_sboxes[i]
		[((block & 1) | ((block >> 5) & 1) << 1)]
		[((block >> 1) & ((1 << 4) - 1))] << (32 - (4 * (i + 1)));
		i++;
	}
	result = permute(result, 32, 32, P_PERMUTE);
	return (result);
}

uint64_t	permute(uint64_t value, int begin, int end, t_permute_type type)
{
	uint64_t	result;
	int			i;

	result = 0;
	i = -1;
	while (++i < end)
	{
		result |= (((value >> (begin - g_tab_permute[type][i])) & 1)
		<< (end - i - 1));
	}
	return (result);
}

// void		permute_subkeys(t_des *des)
// {
// 	int			i;
// 	uint64_t	last_left;
// 	uint64_t	last_right;

// 	i = -1;
// 	last_left = (des->ip >> 32);
// 	last_right = (des->ip & ((1UL << 32) - 1));
// 	while (++i < 16)
// 	{
// 		if (i > 0)
// 		{
// 			last_right = des->p_subkey.right[i - 1];
// 			last_left = des->p_subkey.left[i - 1];
// 		}
// 		des->p_subkey.left[i] = last_right;
// 		des->p_subkey.right[i] = (last_left
// 		^ f(des->p_subkey.left[i], des->subkey[i]));
// 	}
// }

uint64_t	permute_subkeys(uint64_t ip, uint64_t *subkeys)
{
	int			i;
	uint32_t	left;
	uint32_t	left_tmp;
	uint32_t	right;

	i = -1;
	left = ip >> 32;
	right = ip;
	while (++i < 16)
	{
		left_tmp = left;
		left = right;
		right = left_tmp ^ f(left, subkeys[i]);
	}
	return (((uint64_t)right) << 32 | left);
}