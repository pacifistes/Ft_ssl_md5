/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_decode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:09:52 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/18 22:46:05 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t	result_decode(uint64_t block, t_des_info *info,
int options, t_algo algo)
{
	uint64_t	result;
	uint64_t	tmp;

	tmp = (algo == DES_OFB || algo == DES_CTR) ? info->iv : block;
	if (algo == DES_CBC || algo == DES_ECB || algo == DES_PCBC)
		result = des_value(block, info, (options & D) ? 1 : 0);
	else
		result = des_value(info->iv, info, 0);
	result = (algo == DES_CBC) ? result ^ info->iv : result;
	info->iv = (algo == DES_CBC) ? tmp : info->iv;
	result = (algo == DES_PCBC) ? result ^ info->iv : result;
	info->iv = (algo == DES_PCBC) ? tmp ^ result : info->iv;
	result = (algo == DES_CTR) ? result ^ block : result;
	info->iv = (algo == DES_CTR) ? tmp + 1 : info->iv;
	info->iv = (algo == DES_OFB) ? result : info->iv;
	result = (algo == DES_OFB) ? result ^ block : result;
	result = (algo == DES_CFB) ? result ^ block : result;
	info->iv = (algo == DES_CFB) ? tmp : info->iv;
	return (result);
}

static int		apply_des_decode(t_cipher_fd *cipher, t_des_info *info,
int options, t_algo algo)
{
	uint64_t	block;
	uint64_t	result;
	int			i;

	i = 0;
	while (i * 8 < cipher->size_buffer)
	{
		block = create_des_block(cipher->buffer + (i * 8), 8, algo);
		result = result_decode(block, info, options, algo);
		ft_memcpy_uint64(cipher->buffer + i * 8, result);
		i++;
	}
	return (1);
}

static int		check_last_chunk(t_cipher_fd *cipher, int previous_size)
{
	int		i;
	char	last_c;

	i = 0;
	last_c = cipher->buffer[previous_size - 1];
	if (!(last_c >= 1 && last_c <= 8))
		return (0);
	while (i < last_c)
	{
		if (cipher->buffer[previous_size - 1 - i] != last_c)
			return (0);
		i++;
	}
	return (1);
}

static int		fill_buffer(char *buffer, int options, t_cipher_fd *c,
t_des_info *info)
{
	int			lenght;

	if (options & A)
	{
		if (!(options & IS_OFB))
		{
			lenght = decode_block(buffer, c->buffer + info->size_buffer,
			c->size_buffer);
		}
		else
		{
			lenght = decode_block_ofb(buffer, c->buffer + info->size_buffer,
			c->size_buffer);
		}
		if (lenght == 0 && ft_printf("bad decrypt\n"))
			return (0);
		c->size_buffer = lenght + info->size_buffer;
	}
	else
		ft_memcpy(c->buffer + info->size_buffer, buffer, c->size_buffer);
	info->size_buffer = 0;
	if (c->size_buffer % 8 != 0 && !(options & IS_OFB) && ft_printf("bad decrypt2\n"))
		return (0);
	return (1);
}

void			des_decode(t_cipher_fd *c, int opt,
t_algo algo, t_des_info *info)
{
	char		buffer[64];
	int			last_size;
	static int	(*read[])(int, char *, int) = {&read_fd, &read_trim};

	info->iv = (algo == DES_CTR) ? 0 : info->iv;
	if ((last_size = 0) == 0 && info->show_salt && opt & A)
		ft_memcpy(c->buffer, info->buff, info->size_buffer);
	while ((c->size_buffer = ((*read[(opt & A) ? 1 : 0]))(c->in_fd, buffer,
	(opt & A) ? (64 - info->size_buffer) : 48)) > 0)
	{
		(last_size != 0) ? write(c->out_fd, c->buffer, last_size) : 1;
		if (!fill_buffer(buffer, opt | ((algo == DES_OFB) ? IS_OFB : 0), c, info))
			return ;
		apply_des_decode(c, info, opt, algo);
		last_size = c->size_buffer;
	}
	if (last_size == 0 && ((c->size_buffer = info->size_buffer) || 1))
	{
		apply_des_decode(c, info, opt, algo);
		last_size = c->size_buffer;
	}
	if (algo != DES_OFB && !check_last_chunk(c, last_size))
		return (void)ft_printf("bad decrypyt\n");
	write(c->out_fd, c->buffer, last_size - ((algo != DES_OFB)
	? c->buffer[last_size - 1] : 0));
}
