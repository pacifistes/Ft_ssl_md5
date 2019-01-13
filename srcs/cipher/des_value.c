/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:26:54 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 21:20:23 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t	encode_des_block(uint64_t block, t_des *des)
{
	des->ip = permute(block, 64, 64, IP_PERMUTE);
	permute_subkeys(des);
	return (permute((des->p_subkey.right[15] << 32)
	| des->p_subkey.left[15], 64, 64, FINAL_PERMUTE));
}

static uint64_t	decode_des_block(uint64_t block, t_des *des)
{
	uint64_t	reverse;

	reverse = unpermute(block, 64, FINAL_PERMUTE);
	unpermute_subkeys(des, reverse);
	return (unpermute(des->ip, 64, IP_PERMUTE));
}

uint64_t		des_value(uint64_t block, t_des_info *info, int is_decode)
{
	static uint64_t	(*function[])(uint64_t, t_des *) = {
		&encode_des_block,
		&decode_des_block
	};
	t_des			des;
	uint64_t		result;

	des.p_key = permute(info->key, 64, 56, KEY_PERMUTE);
	create_subkeys(des.subkey, des.p_key);
	result = (*function[is_decode])(block, &des);
	return (result);
}
