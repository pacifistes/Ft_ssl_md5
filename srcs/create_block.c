/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 11:42:39 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/28 19:07:19 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	init_and_add_message(t_hash *hash)
{
	int i;
	int i_str;

	i = -1;
	i_str = -1;
	while (++i < 16)
		hash->block[i] = 0;
	while (++i_str < hash->lenght_str)
	{
		hash->block[i_str / 4] |=
		(((unsigned char)(hash->str_block[i_str])) << ((i_str % 4) * 8));
	}
}

static void	add_one_or_size(t_hash *hash, uint64_t size, int is_one_set)
{
	if (is_one_set == 0)
	{
		hash->block[hash->lenght_str / 4] |=
			(1 << (((hash->lenght_str % 4) * 8) + 7));
	}
	if (hash->lenght_str / 4 < 14)
	{
		if (!ft_strcmp("SHA256", hash->info.type))
			size = reverse_u64(size);
		hash->block[14] |= (size & 0xffffffff);
		hash->block[15] |= (size >> 32);
		hash->status = 1;
	}
}

void		create_block(t_hash *hash, char options)
{
	static int		is_one_set = 0;
	static uint64_t	size = 0;
	static int		nbr_block = 0;

	init_and_add_message(hash);
	size += (hash->lenght_str * 8);
	if (hash->lenght_str != 64)
		add_one_or_size(hash, size, is_one_set);
	nbr_block++;
	if (options & D)
		print_block(hash, nbr_block, is_one_set);
	if (hash->status == 1)
	{
		size = 0;
		nbr_block = 0;
		is_one_set = 0;
	}
	else if (hash->lenght_str != 64)
		is_one_set = 1;
}

int bitExtracted(int number, int nbr_bit, int pos) 
{
	return ((((1 << nbr_bit) - 1) & (number >> pos)));
}
