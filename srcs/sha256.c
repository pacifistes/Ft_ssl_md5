/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:28:57 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/26 23:22:55 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t rotr(int n, uint32_t x)
{
	return ((x >> n) | (x << (32 - n)));
}

uint32_t sigma0(uint32_t x)
{
	return rotr(7, x) ^ rotr(18, x) ^ (x >> 3);
}

uint32_t sigma1(uint32_t x)
{
	return rotr(17, x) ^ rotr(19, x) ^ (x >> 10);
}

// static uint32_t	reverse_hash(uint32_t hash)
// {
// 	hash = ((hash & 0x000000FF) << 24) |
// 	((hash & 0x0000FF00) << 8) |
// 	((hash & 0x00FF0000) >> 8) |
// 	((hash & 0xFF000000) >> 24);
// 	return (hash);
// }

static void	init_sha256_values(uint32_t *block, t_sha256_algo *sha256)
{
	static uint32_t	k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

	uint32_t s0;
	uint32_t s1;
	sha256->i = 0;
	while (sha256->i < 64)
	{
		sha256->k[sha256->i] = k[sha256->i];
		sha256->w[sha256->i] = 0;
		sha256->i++;
	}
	sha256->i = 0;

	while (sha256->i < 64)
	{
		if (sha256->i <= 15)
		{
			// sha256->w[sha256->i] = (uint32_t)reverse_hash(block[sha256->i]);
			sha256->w[sha256->i] = block[sha256->i];
		}
		else
		{
			// printf("case 1: %u", sha256->w[sha256->i - 15]);
			s0 = sigma0(sha256->w[sha256->i - 15]);
			// printf("case 1: %u", sha256->w[sha256->i - 15]);
			// exit(1);
			s1 = sigma1(sha256->w[sha256->i - 2]);
			sha256->w[sha256->i] = sha256->w[sha256->i - 16] + s0 + sha256->w[sha256->i - 7] + s1;
		}
		sha256->i++;
	}
}

static void	sha256_loop(u_int32_t **hash, t_sha256_algo *sha256)
{
	uint32_t a = (*hash)[0];
	uint32_t b = (*hash)[1];
	uint32_t c = (*hash)[2];
	uint32_t d = (*hash)[3];
	uint32_t e = (*hash)[4];
	uint32_t f = (*hash)[5];
	uint32_t g = (*hash)[6];
	uint32_t h = (*hash)[7];

	uint32_t S1 = rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25);
	uint32_t CH = (e & f) ^ ((~e) & g);
	uint32_t temp1 = h + S1 + CH + sha256->k[sha256->i] + sha256->w[sha256->i];
	uint32_t S0 = rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22);
	uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
	uint32_t temp2 = S0 + maj;
	h = g;
	g = f;
	f = e;
	e = d + temp1;
	d = c;
	c = b;
	b = a;
	a = temp1 + temp2;

	(*hash)[0]= a;
	(*hash)[1]= b;
	(*hash)[2]= c;
	(*hash)[3]= d;
	(*hash)[4]= e;
	(*hash)[5]= f;
	(*hash)[6]= g;
	(*hash)[7]= h;
}

void	sha256(uint32_t *block, u_int32_t **hash)
{
	uint32_t		old_hash[8];
	t_sha256_algo	sha256;

	old_hash[0] = (*hash)[0];
	old_hash[1] = (*hash)[1];
	old_hash[2] = (*hash)[2];
	old_hash[3] = (*hash)[3];
	old_hash[4] = (*hash)[4];
	old_hash[5] = (*hash)[5];
	old_hash[6] = (*hash)[6];
	old_hash[7] = (*hash)[7];
	init_sha256_values(block, &sha256);
	sha256.i = 0;
	ft_printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3], (*hash)[4], (*hash)[5], (*hash)[6], (*hash)[7]);
	while (sha256.i < 64)
	{
		sha256_loop(hash, &sha256);
		sha256.i++;
	}
	ft_printf("%08x %08x %08x %08x %08x %08x %08x %08x\n", (*hash)[0], (*hash)[1], (*hash)[2], (*hash)[3], (*hash)[4], (*hash)[5], (*hash)[6], (*hash)[7]);
	(*hash)[0] = (*hash)[0] + old_hash[0];
	(*hash)[1] = (*hash)[1] + old_hash[1];
	(*hash)[2] = (*hash)[2] + old_hash[2];
	(*hash)[3] = (*hash)[3] + old_hash[3];
	(*hash)[4] = (*hash)[4] + old_hash[4];
	(*hash)[5] = (*hash)[5] + old_hash[5];
	(*hash)[6] = (*hash)[6] + old_hash[6];
	(*hash)[7] = (*hash)[7] + old_hash[7];
}

void	init_sha256(t_hash *hash)
{
	t_hash_info		info;
	static uint32_t	first_hash[8] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};

	info.size = 8;
	info.hash = first_hash;
	info.type = "SHA256";
	hash->info = info;
	hash->apply_algo = &sha256;
}