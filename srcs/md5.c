/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:24:39 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 21:02:03 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void init_md5_values(t_md5_algo *md5)
{
	static uint32_t tmp_s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15,
		21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	static uint32_t k[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
		0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af,
		0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
		0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453,
		0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
		0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681,
		0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
		0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5,
		0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
		0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0,
		0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	md5->i = 0;
	while (md5->i < 64)
	{
		md5->k[md5->i] = k[md5->i];
		md5->s[md5->i] =tmp_s[md5->i];
		md5->i++;
	}
}

void		md5_loop(uint32_t *block, u_int32_t **hash, t_md5_algo *md5)
{
	if (md5->i <= 15)
		md5->f = ((*hash)[1] & (*hash)[2]) | ((~(*hash)[1]) & (*hash)[3]);
	else if (md5->i <= 31)
		md5->f = ((*hash)[1] & (*hash)[3]) | ((*hash)[2] & (~(*hash)[3]));
	else if (md5->i <= 47)
		md5->f = (*hash)[1] ^ (*hash)[2] ^ (*hash)[3];
	else
		md5->f = (*hash)[2] ^ ((*hash)[1] | (~(*hash)[3]));
	if (md5->i <= 15)
		md5->i_block = md5->i;
	else if (md5->i <= 31)
		md5->i_block = ((5 * md5->i) + 1) % 16;
	else if (md5->i <= 47)
		md5->i_block = ((3 * md5->i) + 5) % 16;
	else
		md5->i_block = (7 * md5->i) % 16;
	md5->f += (*hash)[0] + md5->k[md5->i] + block[md5->i_block];
	(*hash)[0] = (*hash)[3];
	(*hash)[3] = (*hash)[2];
	(*hash)[2] = (*hash)[1];
	(*hash)[1] = (*hash)[1]
	+ ((md5->f << md5->s[md5->i]) | (md5->f >> (32 - md5->s[md5->i])));
}

void		md5(uint32_t *block, u_int32_t **hash)
{
	uint32_t 	old_hash[4];
	t_md5_algo	md5;		
	
	old_hash[0] = (*hash)[0];
	old_hash[1] = (*hash)[1];
	old_hash[2] = (*hash)[2];
	old_hash[3] = (*hash)[3];
	ft_printf("old value:\n%08x\n%08x\n%08x\n%08x\n", old_hash[0], old_hash[1], old_hash[2], old_hash[3]);
	print_block(block, 16);
	init_md5_values(&md5);
	md5.i = 0;
	while (md5.i < 64)
	{
		md5_loop(block, hash, &md5);
		md5.i++;
	}
	ft_printf("old value:\n%08x\n%08x\n%08x\n%08x\n", old_hash[0], old_hash[1], old_hash[2], old_hash[3]);
	(*hash)[0] = (*hash)[0] + old_hash[0];
	(*hash)[1] = (*hash)[1] + old_hash[1];
	(*hash)[2] = (*hash)[2] + old_hash[2];
	(*hash)[3] = (*hash)[3] + old_hash[3];
}

void		init_md5(t_hash *hash)
{
	t_hash_info info;
	static uint32_t first_hash[4] = {0x67452301, 0xefcdab89,
									0x98badcfe, 0x10325476};

	info.size = 4;
	info.hash = first_hash;
	info.type = "MD5";
	hash->info = info;
	hash->apply_algo = &md5;
}

