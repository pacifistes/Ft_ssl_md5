/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:09:52 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 22:48:55 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			apply_des_decode(t_cipher_fd *cipher, t_des_info *info, int options,
t_algo algo)
{
	uint64_t	block;
	uint64_t	result;
	uint64_t	original_block;
	int			i;

	i = 0;
	while (i * 8 < cipher->size_buffer)
	{
		block = create_des_block(cipher->buffer, 8);
		original_block = block;
		if (algo == DES_CBC)
			block = block ^ info->iv;
		if (algo == DES_PCBC)
		{
			block = block ^ info->iv;
		}
		if (algo == DES_CBC || algo == DES_ECB || algo == DES_PCBC)
			result = des_value(block, info, (options & D) ? 1 : 0);
		else
			result = des_value(info->iv, info, (options & D) ? 1 : 0);
		if (algo == DES_CFB)
		{
			result ^= block;
			info->iv = result;
		}
		if (algo == DES_OFB)
		{
			info->iv = result;
			result ^= block;
		}
		if (algo == DES_OFB)
		{
			info->iv += 1;
			result ^= block;
		}
		if (algo == DES_PCBC)
		{
			info->iv = result ^ original_block;
		}
		if (algo == DES_CBC)
			info->iv = result;
		ft_memcpy_uint64(cipher->buffer + i * 8, result);
		i++;
	}
	return (1);
}
int			check_last_chunk(t_cipher_fd *cipher, int previous_size)
{
	int i;

	i = 0;
	if (cipher->buffer[previous_size - 1] >= 1 && cipher->buffer[previous_size - 1] <= 8)
	{
		while (i < cipher->buffer[previous_size - 1])
		{
			if (cipher->buffer[previous_size - 1 - i] != cipher->buffer[previous_size - 1])
				return (0);
			i++;
		}
	}
	else
	{
		ft_printf("[%d][%c]\n", cipher->buffer[previous_size - 1], cipher->buffer[previous_size - 1]);
		return (0);
	}
	return (1);
}

void		des_decode(t_cipher_fd *cipher, int options,
t_algo algo, t_des_info	*info)
{
	char	buffer[64];
	int		lenght;
	int		(*read[])(int fd, char *buff, int size) = {&read_fd, &read_fd_without_space};
	int		previous_size;

	previous_size = 0;
	if (info->show_salt && options & A)
		ft_memcpy(cipher->buffer, info->buff, info->size_buffer);
	while ((cipher->size_buffer = ((*read[(options & A) ? 1 :0]))(cipher->in_fd, buffer, (options & A) ? (64 - info->size_buffer) : 48)) > 0)
	{
		if (previous_size != 0)
			write(cipher->out_fd, cipher->buffer, previous_size);
		if (options & A)
		{
			lenght = decode_block(buffer, cipher->buffer + info->size_buffer, cipher->size_buffer);
			if (lenght == 0)
			{
				ft_printf("bad decrypt\n");
				return ;
			}
			ft_printf("size = %d\n", cipher->size_buffer);
			cipher->size_buffer = lenght + info->size_buffer;
			ft_printf("size = %d|%d\n", cipher->size_buffer, lenght);
		}
		else
		{
			ft_memcpy(cipher->buffer + info->size_buffer, buffer, cipher->size_buffer);
		}
		if (info->size_buffer > 0)
			info->size_buffer = 0;
		if (cipher->size_buffer % 8 != 0)
		{
			ft_printf("size = %d\n", cipher->size_buffer);
			ft_printf("bad decrypt\n");
			return ;
		}
		apply_des_decode(cipher, info, options, algo);
		previous_size = cipher->size_buffer;
	}
	// if (!check_last_chunk(cipher, previous_size))
	// 	ft_printf("bad decryppppt\n");
	// else
	write(cipher->out_fd, cipher->buffer, previous_size);
		// write(cipher->out_fd, cipher->buffer, previous_size - cipher->buffer[previous_size - 1]);

}