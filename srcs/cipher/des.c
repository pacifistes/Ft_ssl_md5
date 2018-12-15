/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:14:50 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/15 22:19:17 by bbrunell         ###   ########.fr       */
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

static int	g_tab_permute[][64] = {
	{
		57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18, 10, 2, 59, 51, 43,
		35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7, 62,
		54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
	},
	{
		14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4, 26, 8,
		16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
	},
	{
		58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
		62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
		57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
		61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
	},
	{
		32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9, 8, 9, 10, 11, 12, 13, 12, 13, 14,
		15, 16, 17, 16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25, 24, 25, 26,
		27, 28, 29, 28, 29, 30, 31, 32, 1
	},
	{
		16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10, 2, 8, 24,
		14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
	},
	{
		40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
		38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
		36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
		34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
	}
};

/*
**	params : char[8], int key
*/

uint64_t	permute(uint64_t value, int size_begin, int size_end,
t_permute_type type)
{
	uint64_t	result;
	int			i;

	result = 0;
	i = -1;
	while (++i < size_end)
	{
		result |= (((value >> (size_begin - g_tab_permute[type][i])) & 1)
		<< (size_end - i - 1));
	}
	return (result);
}

uint64_t	reverse_permute(uint64_t value, int size, t_permute_type type)
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

uint64_t	left_rotate(uint64_t value, int shift, int size_value)
{
	uint64_t result;

	result = (((value << (64 - size_value + shift)) >> (64 - size_value))
	| (value >> (size_value - shift)));
	return (result);
}


void		create_subkeys(uint64_t *subkeys, uint64_t p_key)
{
	uint64_t	c;
	uint64_t	d;
	int			shift;
	int			i;

	i = 0;
	c = p_key >> 28;
	d = bitExtracted(p_key, 28, 0);
	while (i < 16)
	{
		shift = (i < 2 || i == 8 || i == 15) ? 1 : 2;
		c = left_rotate(c, shift, 28);
		d = left_rotate(d, shift, 28);
		subkeys[i] = permute((c << 28) | d, 56, 48, SUBKEY_PERMUTE);
		i++;
	}
}

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
		block = bitExtracted(new_right, 6, 48 - ((i + 1) * 6));
		result |= g_sboxes[i]
		[((block & 1) | ((block >> 5) & 1) << 1)]
		[((block >> 1) & ((1 << 4) - 1))] << (32 - (4 * (i + 1)));
		i++;
	}
	result = permute(result, 32, 32, P_PERMUTE);
	return (result);
}

void	permute_subkeys(t_des *des)
{
	int			i;
	uint64_t	last_left;
	uint64_t	last_right;

	i = -1;
	last_left = (des->ip >> 32);
	last_right = (des->ip & ((1UL << 32) - 1));
	while (++i < 16)
	{
		if (i > 0)
		{
			last_right = des->p_subkey.right[i - 1];
			last_left = des->p_subkey.left[i - 1];
		}
		des->p_subkey.left[i] = last_right;
		des->p_subkey.right[i] = (last_left ^ f(des->p_subkey.left[i], des->subkey[i]));
	}
}

void	reverse_permute_subkeys(t_des *des, uint64_t reverse)
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
		des->p_subkey.left[i] = (previous_right ^ f(des->p_subkey.right[i], des->subkey[i + 1]));
		i--;
	}
	des->ip = (((des->p_subkey.right[0] ^ f(des->p_subkey.left[0], des->subkey[0])) << 32) | (des->p_subkey.left[0]));
	// ft_printf("ip = %064llb\n", des->ip);
}

void	encode_des_ecb(uint64_t block, uint64_t key)
{
	t_des		des;
	uint64_t	result;

	des.p_key = permute(key, 64, 56, KEY_PERMUTE);
	create_subkeys(des.subkey, des.p_key);
	des.ip = permute(block, 64, 64, IP_PERMUTE);
	// ft_printf("ip = %064llb\n", des.ip);
	permute_subkeys(&des);
	// ft_printf("subkey =%064llb\n", (des.p_subkey.right[15] << 32)
	// | des.p_subkey.left[15]);
	result = permute((des.p_subkey.right[15] << 32)
	| des.p_subkey.left[15], 64, 64, FINAL_PERMUTE);
	// ft_printf("block = %064llb\n", result);

	// ft_printf("%llx\n", result);
}

void	decode_des_ecb(uint64_t block, uint64_t key)
{
	t_des		des;
	uint64_t	reverse;
	uint64_t	result;
	
	des.p_key = permute(key, 64, 56, KEY_PERMUTE);
	create_subkeys(des.subkey, des.p_key);
	// ft_printf("block = %064llb\n", block);
	reverse = reverse_permute(block, 64, FINAL_PERMUTE);
	// ft_printf("subkey =%064llb\n", reverse);
	reverse_permute_subkeys(&des, reverse);
	result = reverse_permute(des.ip, 64, IP_PERMUTE);
	// ft_printf("decode = %llx\n", result);

}

void    print_salt(uint64_t salt, int fd)
{
	char	buffer[9];
	int		i;

	ft_bzero(buffer, 9);
	i = 0;
	while (i < 8)
	{
		buffer[i] = ((salt >> (56 - (8 * i))) & 0xff);
		i++;
	}
	ft_putstr_fd("Salted__", fd);
	ft_putstr_fd(buffer, fd);
}

void	des(t_cipher_commands *c, t_cipher_fd *cipher, int options, t_algo algo)
{
	t_des_info	info;
	int			status;
	uint64_t	block;

	ft_bzero(&info, sizeof(t_des_info));
	block = 0;
	status = init_des_info(c, &info);
	if (info.show_salt)
		print_salt(info.salt, cipher->out_fd);
	if (!status)
		return ;
	if (options & MAJ_P)
	{
		ft_printf("salt=%016llx\n", info.salt);
		ft_printf("key=%016llx\n", info.key);
		if (algo == DES_CBC)
			ft_printf("iv=%016llx\n", info.iv);
	}

	// while (cipher->status == 0)
	// {
	// 	ft_printf("plop\n");
	// 	if ((cipher->size_buffer = read_fd(cipher->in_fd, cipher->buffer,
	// 	8)) == -1)
	// 	{
	// 		ft_printf("No such file or directory\n");
	// 		break ;
	// 	}
	// 	for (int j=0;j < 8; j++) { block |= ((unsigned char *)cipher)[j] << (8 * j); }
	// 	// encode_des_ecb(block, info.key);
	// 	block = 0;
	// 	// ft_bzero(cipher->buffer, sizeof(char) * 8);
	// 	// if (cipher->status == 1)
	// 	// 	break ;
	// 	return ;
	// }
	(void)cipher;
}