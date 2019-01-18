/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:14:50 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/18 15:02:08 by bbrunell         ###   ########.fr       */
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

static int	is_valid_file(char *salt_buff, int size, int options)
{
	int	status;

	status = 1;
	if (size == -1)
	{
		ft_printf("No such file or directory\n");
		status = 0;
	}
	if (ft_strncmp(salt_buff, "Salted__", 8))
	{
		ft_printf("bad magic Number\n");
		status = 0;
	}
	if ((options & A && (size < 16))
	|| (!(options & A) && size < 16))
	{
		ft_printf("error reading input file\n", size);
		status = 0;
	}
	return (status);
}

static int	register_salt(t_cipher_commands *c, t_cipher_fd *cipher,
t_des_info *info, int options)
{
	t_salt_buffers	s;
	int				size;
	t_hash_info		h;

	if (options & A)
	{
		size = read_trim(cipher->in_fd, s.buff_base64, 64);
		if ((size = decode_block(s.buff_base64, s.buff_tmp, size)) == 0
		&& ft_printf("error reading input file\n"))
			return (0);
		ft_memcpy(s.buff, s.buff_tmp, 16);
		info->size_buffer = size - 16;
		ft_memcpy(info->buff, s.buff_tmp + 16, info->size_buffer);
	}
	else
		size = read_fd(cipher->in_fd, s.buff, 16);
	if (!is_valid_file(s.buff, size, options))
		return (0);
	ft_memcpy(&info->salt, s.buff + 8, 8);
	if ((info->salt = reverse_u64(info->salt)) == info->salt && !c->options.key)
		h = create_hash(c->options.password, info->salt);
	if (!c->options.key)
		info->key = reverse_u64(h.hash[0]) | reverse_u32(h.hash[1]);
	return (1);
}

static void	print_information(t_des_info *info, t_algo algo)
{
	ft_printf("salt=%016llx\n", info->salt);
	ft_printf("key=%016llx\n", info->key);
	if (algo == DES_CBC)
		ft_printf("iv=%016llx\n", info->iv);
}

void		des(t_cipher_commands *c, t_cipher_fd *cipher, int options,
t_algo algo)
{
	t_des_info	info;
	int			status;

	ft_bzero(&info, sizeof(t_des_info));
	status = init_des_info(c, &info, algo, options);
	if (info.show_salt && !(options & (MAJ_P | D | A)))
	{
		print_salt(info.salt, cipher->out_fd);
		info.show_salt = 0;
	}
	if (status && info.show_salt && options & D)
		status = register_salt(c, cipher, &info, options);
	if (!status)
		return ;
	if (options & MAJ_P || options & L)
	{
		print_information(&info, algo);
		if (options & MAJ_P)
			return ;
	}
	if (!(options & D))
		des_encode(cipher, options, algo, &info);
	else
		des_decode(cipher, options, algo, &info);
}
