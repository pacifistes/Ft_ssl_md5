/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:26:54 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 18:04:17 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t	left_rotate(uint64_t value, int shift, int size_value)
{
	uint64_t result;

	result = (((value << (64 - size_value + shift)) >> (64 - size_value))
	| (value >> (size_value - shift)));
	return (result);
}

static void		create_subkeys(uint64_t *subkeys, uint64_t p_key)
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

static uint64_t	encode_des_block(uint64_t block, uint64_t *subkeys)
{
	uint64_t	permute_subkey;
	uint64_t	ip;

	ip = permute(block, 64, 64, IP_PERMUTE);
	permute_subkey = permute_subkeys(ip, subkeys);
	return (permute(permute_subkey, 64, 64, FINAL_PERMUTE));
}

static uint64_t	decode_des_block(uint64_t block, uint64_t *subkeys)
{
	uint64_t	reverse;
	uint64_t	ip;

	reverse = unpermute(block, 64, FINAL_PERMUTE);
	ip = unpermute_subkeys(reverse, subkeys);
	return (unpermute(ip, 64, IP_PERMUTE));
}

uint64_t		des_value(uint64_t block, t_des_info *info, int is_decode)
{
	static uint64_t	(*function[])(uint64_t block, uint64_t *subkeys) = {
		&encode_des_block,
		&decode_des_block
	};
	uint64_t		permute_key;
	uint64_t		subkeys[16];

	permute_key = permute(info->key, 64, 56, KEY_PERMUTE);
	create_subkeys(subkeys, permute_key);
	return ((*function[is_decode])(block, subkeys));
}
