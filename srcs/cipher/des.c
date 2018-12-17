/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:14:50 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/17 16:19:39 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	params : char[8], int key
*/

static void	print_salt(uint64_t salt, int fd)
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
	write(fd, buffer, 8);
}

int			init_des(t_cipher_commands *c, t_des_info *info,
t_cipher_fd *cipher, t_algo algo)
{
	int			status;

	ft_bzero(info, sizeof(t_des_info));
	status = init_des_info(c, info, algo);
	if (info->show_salt)
		print_salt(info->salt, cipher->out_fd);
	if (!status)
		return (0);
	return (1);
}

void	des(t_cipher_commands *c, t_cipher_fd *cipher, int options, t_algo algo)
{
	t_des_info	info;
	uint64_t	block;
	uint64_t	result;
	char		buffer[48];
	int			size_buffer;

	if (!init_des(c, &info, cipher, algo))
		return ;
	if (options & MAJ_P)
	{
		ft_printf("salt=%016llx\n", info.salt);
		ft_printf("key=%016llx\n", info.key);
		if (algo == DES_CBC)
			ft_printf("iv=%016llx\n", info.iv);
	}
	ft_bzero(buffer, sizeof(char) * 48);
	size_buffer = 0;
	block = 0;
	while ((cipher->size_buffer = read_fd(cipher->in_fd, cipher->buffer,
		8)) > 0)
	{
		for (int j=0;j < cipher->size_buffer; j++) { block |= ((uint64_t)(((unsigned char *)cipher)[j])) << (56 - 8 * j); }
		for (int h = cipher->size_buffer; h < 8; h++) {block |= 	((uint64_t) cipher->size_buffer % 8) << (56 - 8 * h);}
		result = des_value(block, info.key, options & D);
		for (int j=0;j < 8; j++)
		{
			buffer[size_buffer + j] = result >> (56 - (8 * j));
		}
		block = 0;
		size_buffer += 8;
		if (size_buffer == 48)
		{
			write(cipher->out_fd, buffer, size_buffer);
			ft_bzero(buffer, sizeof(char) * 48);
			size_buffer = 0;
		}
		if (cipher->size_buffer < 8)
			break ;
	}
	if (cipher->size_buffer == 0)
	{
		for (int i = 0; i < 8; i++) {block |= 	(8UL << (56 - 8 * i));}
		result = des_value(block, info.key, options & D);
		for (int j=0;j < 8; j++)
		{
			buffer[size_buffer + j] = result >> (56 - (8 * j));
		}
		block = 0;
		size_buffer += 8;
	}
	write(cipher->out_fd, buffer, size_buffer);
	if (cipher->size_buffer == -1)
		ft_printf("No such file or directory\n");
}
