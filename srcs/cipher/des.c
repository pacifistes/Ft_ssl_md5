/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:14:50 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/12 19:34:00 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	g_sboxes[8][4][16] = {
		{
			{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
			{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
			{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
			{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
		},
		{
			{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
			{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
			{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
			{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
		},
		{
			{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
			{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
			{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
			{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
		},
		{
			{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
			{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
			{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
			{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
		},
		{
			{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
			{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
			{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
			{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
		},
		{
			{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
			{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
			{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
			{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
		},
		{
			{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
			{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
			{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
			{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
		},
		{
			{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
			{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
			{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
			{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11},
		}
	};

/*
**	params : char[8], int key
*/

typedef struct	s_plop
{
	uint64_t right[16];
	uint64_t left[16];
}				t_plop;

typedef struct	s_subkeys
{
	uint64_t subkey[16];
}				t_subkeys;

uint64_t	permute_key_1(uint64_t key)
{
	uint64_t pc_1;
	int i_old_bit;
	int	i;
	int	i_new_bit;

	i_new_bit = 63;
	i_old_bit = 57;
	i = 0;
	pc_1 = 0;
	while (i < 56)
	{
		pc_1 |= (((key >> (64 - i_old_bit)) & (1 << 0)) << i_new_bit);
		i++;
		if (i_old_bit > 8)
			i_old_bit = (i_old_bit == 36) ? 63 : i_old_bit - 8;
		else if (i_old_bit < 4)
			i_old_bit = 65 - (8 - i_old_bit);
		else if (i_old_bit < 8)
			i_old_bit = (i_old_bit == 5) ? 8 : 63 - (8 - i_old_bit);
		i_new_bit--;
	}
	return (pc_1);
}

uint64_t	permute_ip(uint64_t value)
{
	static int	tab[64] = {58, 50, 42, 34, 26, 18, 10, 2,
						60, 52, 44, 36, 28, 20, 12, 4,
						62, 54, 46, 38, 30, 22, 14, 6,
						64, 56, 48, 40, 32, 24, 16, 8,
						57, 49, 41, 33, 25, 17,  9, 1,
						59, 51, 43, 35, 27, 19, 11, 3,
						61, 53, 45, 37, 29, 21, 13, 5,
						63, 55, 47, 39, 31, 23, 15, 7};
	uint64_t	result;
	int			i;

	result = 0;
	i = 0;
	while (i < 64)
	{
		result |= (((value >> (64 - tab[i])) & 1) << (64 - i - 1));
		i++;
	}
	return (result);
}

uint64_t	permute_key_2(uint64_t key)
{
	static int	tab[48] = {14, 17, 11, 24, 1, 5,
						3, 28, 15, 6, 21, 10,
						23, 19, 12, 4, 26, 8,
						16, 7, 27, 20, 13, 2,
						41, 52, 31, 37, 47, 55,
						30, 40, 51, 45, 33, 48,
						44, 49, 39, 56, 34, 53,
						46, 42, 50, 36, 29, 32};
	uint64_t	pc_2;
	int			i;

	pc_2 = 0;
	i = 0;
	while (i < 48)
	{
		pc_2 |= (((key >> (56 - tab[i])) & 1) << (48 - i - 1));
		i++;
	}
	return (pc_2);
}

void		create_subkeys(t_subkeys *subkeys, uint64_t pc_1)
{
	uint32_t	c;
	uint32_t	d;
	int			shift;
	int			i;

	i = 0;
	c = pc_1 >> (64 - 28);
	d = bitExtracted(pc_1, 28, 8);
	while (i < 16)
	{
		shift = (i < 2 || i == 8 || i == 15) ? 1 : 2;
		c = ((c << (4 + shift)) >> 4) | (c >> (28 - shift));
		d = ((d << (4 + shift)) >> 4) | (d >> (28 - shift));
		subkeys->subkey[i] = permute_key_2((((uint64_t)c) << 28) | d);
		ft_printf("%048llb\n", subkeys->subkey[i]);
		i++;
	}
}

uint64_t	e(uint64_t value)
{
	uint64_t result;
	static int	tab[48] = {32, 1, 2, 3, 4, 5,
							4, 5, 6, 7, 8, 9,
							8, 9,10, 11, 12,13,
							12, 13,14, 15, 16,17,
							16, 17,18, 19, 20,21,
							20, 21,22, 23, 24,25,
							24, 25,26, 27, 28,29,
							28, 29,30, 31, 32, 1};
	int			i;

	result = 0;
	i = 0;
	while (i < 48)
	{
		result |= (((value >> (32 - tab[i])) & 1) << (48 - i - 1));
		i++;
	}
	return (result);
}

uint64_t	p(uint64_t value)
{
	uint64_t result;
	static int	tab[32] = {
					16, 7, 20, 21, 29, 12, 28, 17, 1, 15,
					23, 26, 5, 18, 31, 10, 2, 8, 24, 14, 32,
					27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
					};
	int			i;

	result = 0;
	i = 0;
	while (i < 32)
	{
		result |= (((value >> (32 - tab[i])) & 1) << (32 - i - 1));
		i++;
	}
	return (result);
}

uint64_t	f(uint64_t right, uint64_t key)
{
	uint64_t new_right;
	uint64_t	result;
	int		i;
	uint8_t		block;
	new_right = e(right) ^ key;
	i = 0;
	result = 0;
	while (i < 8)
	{
		block = bitExtracted(new_right, 6, 48 - ((i + 1) * 6));
		result |= g_sboxes[i]
		[((block & 1) | ((block >> 5) & 1) << 1)]
		[((block >> 1) & ((1 << 4) - 1))] << (32 - (4 * (i + 1)));
		i++;
	}
	result = p(result);
	return (result);
}

uint64_t	final_permute(uint64_t value)
{
	static int	tab[64] = {40, 8, 48, 16, 56, 24, 64, 32,
							39, 7, 47, 15, 55, 23, 63, 31,
							38, 6, 46, 14, 54, 22, 62, 30,
							37, 5, 45, 13, 53, 21, 61, 29,
							36, 4, 44, 12, 52, 20, 60, 28,
							35, 3, 43, 11, 51, 19, 59, 27,
							34, 2, 42, 10, 50, 18, 58, 26,
							33, 1, 41, 9, 49, 17, 57, 25};
	uint64_t	result;
	int			i;

	result = 0;
	i = 0;
	while (i < 64)
	{
		result |= (((value >> (64 - tab[i])) & 1) << (64 - i - 1));
		i++;
	}
	return (result);
}

void	des_ecb(uint64_t block, uint64_t key)
{
	uint32_t left;
	uint32_t right;
	uint64_t pc_1;
	uint64_t ip;
	uint64_t result;
	int		i;
	t_subkeys subkeys;
	t_plop plop;

	left = (block >> 32);
	right = (block & 0xFFFFFFFF);
	pc_1 = permute_key_1(key);
	create_subkeys(&subkeys, pc_1);
	ip = permute_ip(block);

	i = 0;
	while (i < 16)
	{
		plop.left[i] = (i == 0) ? (ip & ((1UL << 32) - 1)) : plop.right[i - 1];
		plop.right[i] = (i == 0) ? ((ip >> 32) ^ f(plop.left[i], subkeys.subkey[i]))
		: (plop.left[i - 1] ^ f(plop.left[i], subkeys.subkey[i]));
		i++;
	}
	ft_printf("final\nleft = %032llb\nright = %032llb\n", plop.left[15], plop.right[15]);
	result = final_permute((plop.right[15] << 32) | plop.left[15]);
	ft_printf("result = %0llx\n", result);

}
