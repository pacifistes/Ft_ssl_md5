/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_encode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:09:57 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 21:21:12 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
void			add_salt_to_buffer(char *buffer, int *size_buffer, t_des_info *info)
{
	ft_memcpy(buffer, "Salted__", 8);
	ft_memcpy_uint64(buffer + 8, info->salt);
	info->show_salt = 0;
	*size_buffer += 16;
}

void			apply_des_encode(t_cipher_fd *cipher, t_des_info *info, int options,
t_algo algo)
{
	static char	buffer[48];
	static int	size_buffer = 0;
	uint64_t	block;
	uint64_t	original_block;
	uint64_t	result;

	if (info->show_salt)
		add_salt_to_buffer(buffer, &size_buffer, info);
	block = create_des_block(cipher->buffer, cipher->size_buffer);
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



	ft_memcpy_uint64(buffer + size_buffer, result);
	size_buffer += 8;
	if (size_buffer == 48 || cipher->size_buffer < 8)
	{
		if (options & A)
			base64_encode_str(cipher, buffer, size_buffer);
		else
			write(cipher->out_fd, buffer, size_buffer);
		size_buffer = 0;
	}
}

void		des_encode(t_cipher_fd *cipher, int options,
t_algo algo, t_des_info	*info)
{
	if (algo == DES_CTR)
		info->iv = 0;
	while ((cipher->size_buffer = read_fd(cipher->in_fd, cipher->buffer, 8))
	> 0)
	{
		apply_des_encode(cipher, info, options, algo);
		if (cipher->size_buffer < 8)
			break ;
	}
	if (cipher->size_buffer == 0)
		apply_des_encode(cipher, info, options, algo);
	if (cipher->size_buffer == -1)
		ft_printf("No such file or directory\n");
}

