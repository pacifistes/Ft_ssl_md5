/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:42:39 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 20:39:43 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// uint32_t *create_block(int *ret, char *str, int lenght_str)
// {
// 	static int is_one_set = 0;
// 	static uint64_t size = 0;
// 	uint32_t *block;
// 	int i_str;
// 	int i_block;

// 	i_str = 0;
// 	i_block = 0;
// 	block = (uint32_t*)malloc(sizeof(uint32_t) * 16);
// 	for (int i=0;i<16;i++) {block[i] = 0;}
// 	while (i_str < lenght_str)
// 	{
// 		block[i_str / 4] |= (str[i_str] << (((i_str % 4) * 8)));
// 		i_str++;
// 	}
// 	if (lenght_str != 64) {
// 		i_block = lenght_str / 4;
// 		if (is_one_set == 0)
// 	 	{
// 			size += (lenght_str * 8);
// 			block[i_block] = 0;
// 			block[i_block] |= (1 << (((lenght_str % 4) * 8) + 7));
// 			is_one_set = 1;
// 			i_block++;
// 		}
// 		if (i_block < 14)
// 		{
// 			while (i_block < 14)
// 			{
// 				block[i_block] = 0;
// 				i_block++;
// 			}
// 			block[i_block] = 0;
// 			block[i_block] |= (size >> 32);
// 			block[i_block + 1] = 0;
// 			block[i_block + 1] |= (size & 0xffffffff);
// 			is_one_set = 0;
// 			size = 0;
// 			*ret = 1;
// 			return (block);
// 		}
// 		else
// 		{
// 			while (i_block < 16)
// 			{
// 				block[i_block] = 0;
// 				i_block++;
// 			}
// 		}
// 	}
// 	else {
// 		size += 512;
// 	}
// 	*ret = 0;
// 	return block;
// }

void print_block(uint32_t *block, int lenght)
{
	int i;

	i = 0;
	ft_printf("BLOC:\n");
	while (i < lenght) {
		ft_printf("%h08b %h08b %h08b %h08b\n", ((block[i] & 0xFF000000) >> 24), ((block[i] & 0x00FF0000) >> 16), ((block[i] & 0x0000FF00) >> 8), ((block[i] & 0x000000FF)));
		i++;
	}
}

uint32_t *create_block(int *ret, char *str, int lenght_str)
{
	static int is_one_set = 0;
	static uint64_t size = 0;
	uint32_t *block;
	int i_str;
	int i_block;
	// int j;
	i_str = 0;
	i_block = 0;
	// j = 0;
	block = (uint32_t*)malloc(sizeof(uint32_t) * 16);
	for (int i=0;i<16;i++) {block[i] = 0;}
	while (i_str < lenght_str)
	{
		// j = 0;
		// while (j < )
		block[i_str / 4] |= (str[i_str] << (24 - (((i_str % 4) * 8))));
		// block[i_str / 4] |= (str[i_str] << ((((i_str % 4) * 8))));
		i_str++;
	}
	if (lenght_str != 64) {
		i_block = lenght_str / 4;
		if (is_one_set == 0)
	 	{
			size += (lenght_str * 8);
			block[i_block] = 0;
			block[i_block] |= (1 << (((lenght_str % 4) * 8) + 7));
			is_one_set = 1;
			i_block++;
		}
		if (i_block < 14)
		{
			while (i_block < 14)
			{
				block[i_block] = 0;
				i_block++;
			}
			block[i_block] = 0;
			block[i_block] |= (size >> 32);
			block[i_block + 1] = 0;
			block[i_block + 1] |= (size & 0xffffffff);
			is_one_set = 0;
			size = 0;
			*ret = 1;
			print_block(block, 16);
			return (block);
		}
		else
		{
			while (i_block < 16)
			{
				block[i_block] = 0;
				i_block++;
			}
		}
	}
	else {
		size += 512;
	}
	*ret = 0;
	return block;
}

// 00000000 00000000 00000000 00000000