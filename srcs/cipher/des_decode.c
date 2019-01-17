/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:09:52 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/17 19:11:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	result_decode(uint64_t block, t_des_info *info,
int options, t_algo algo)
{
	uint64_t	original_block;
	uint64_t	result;

	original_block = block;
	result = des_value((algo == DES_CBC || algo == DES_ECB || algo == DES_PCBC)
	? block : info->iv, info, (options & D) ? 1 : 0);
	(void)original_block;
	return (result);
}

/*
**	if (CBC)
**		tmp = block
**		result = decode
**		result ^= iv
**		iv = tmp
**	if (PCBC)
**		tmp = block
**		result = decode
**		result ^= iv
**		iv = tmp ^ result
**	if (OFB)
**		tmp = block
**		result = decode
**		iv = tmp
**		result ^= tmp
*/

int			apply_des_decode(t_cipher_fd *cipher, t_des_info *info, int options,
t_algo algo)
{
	uint64_t	block;
	uint64_t	result;
	int			i;

	i = 0;
	while (i * 8 < cipher->size_buffer)
	{
		block = create_des_block(cipher->buffer + (i * 8), 8);
		result = result_decode(block, info, options, algo);
		ft_memcpy_uint64(cipher->buffer + i * 8, result);
		i++;
	}
	return (1);
}

int			check_last_chunk(t_cipher_fd *cipher, int previous_size)
{
	int		i;
	char	last_c;

	i = 0;
	last_c = cipher->buffer[previous_size - 1];
	if (last_c >= 1 && last_c <= 8)
	{
		while (i < last_c)
		{
			if (cipher->buffer[previous_size - 1 - i] != last_c)
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void		des_decode(t_cipher_fd *cipher, int options,
t_algo algo, t_des_info *info)
{
	char		buffer[64];
	int			lenght;
	static int	(*read[])(int fd, char *buff, int size) = {&read_fd,
											&read_fd_without_space};
	int			previous_size;

	previous_size = 0;
	if (info->show_salt && options & A)
		ft_memcpy(cipher->buffer, info->buff, info->size_buffer);
	while ((cipher->size_buffer = ((*read[(options & A) ? 1
	: 0]))(cipher->in_fd, buffer, (options & A) ? (64 - info->size_buffer)
	: 48)) > 0)
	{
		if (previous_size != 0)
			write(cipher->out_fd, cipher->buffer, previous_size);
		if (options & A)
		{
			lenght = decode_block(buffer, cipher->buffer + info->size_buffer,
			cipher->size_buffer);
			if (lenght == 0)
			{
				ft_printf("bad decrypt\n");
				return ;
			}
			cipher->size_buffer = lenght + info->size_buffer;
		}
		else
		{
			ft_memcpy(cipher->buffer + info->size_buffer, buffer,
			cipher->size_buffer);
		}
		if (info->size_buffer > 0)
			info->size_buffer = 0;
		if (cipher->size_buffer % 8 != 0)
		{
			ft_printf("bad decrypt\n");
			return ;
		}
		apply_des_decode(cipher, info, options, algo);
		previous_size = cipher->size_buffer;
	}
	if (previous_size == 0)
	{
		cipher->size_buffer = info->size_buffer;
		apply_des_decode(cipher, info, options, algo);
		previous_size = cipher->size_buffer;
	}
	if (!check_last_chunk(cipher, previous_size))
		ft_printf("bad decrypt\n");
	else
	{
		write(cipher->out_fd, cipher->buffer,
		previous_size - cipher->buffer[previous_size - 1]);
	}
}
