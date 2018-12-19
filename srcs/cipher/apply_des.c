/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_des.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:14:12 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/19 16:17:14 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t	create_des_block(char *str, int lenght)
{
	int			i;
	int			j;
	uint64_t	block;

	i = 0;
	block = 0;
	while (i < lenght)
	{
		block |= ((uint64_t)(((unsigned char *)str)[i])) << (56 - 8 * i);
		i++;
	}
	j = i;
	while (j < 8)
	{
		block |= ((uint64_t)(8 - (lenght % 8))) << (56 - 8 * j);
		j++;
	}
	return (block);
}

static void		memcpy_des(char *str, int lenght, uint64_t result)
{
	int i;

	i = 0;
	while (i < 8)
	{
		str[lenght + i] = result >> (56 - (8 * i));
		i++;
	}
}

static void		print_des(t_cipher_fd *cipher, char *str, int lenght,
int print_base64)
{
	if (print_base64)
		base64_encode_str(cipher, str, lenght);
	else
		write(cipher->out_fd, str, lenght);
}

void			apply_des(t_cipher_fd *cipher, t_des_info *info, int options,
t_algo algo)
{
	static char	buffer[48];
	static int	size_buffer = 0;
	uint64_t	block;
	uint64_t	result;

	if (size_buffer == 0)
		ft_bzero(buffer, sizeof(char) * 48);
	if (cipher->size_buffer == 0)
		block = create_des_block(NULL, cipher->size_buffer);
	else
		block = create_des_block(cipher->buffer, cipher->size_buffer);
	result = des_value(block, info, (options & D) ? 1 : 0, algo);
	memcpy_des(buffer, size_buffer, result);
	size_buffer += 8;
	if (size_buffer == 48 || cipher->size_buffer < 8)
	{
		print_des(cipher, buffer, size_buffer, options & A);
		size_buffer = 0;
	}
}