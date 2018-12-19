/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:14:50 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/19 15:16:55 by bbrunell         ###   ########.fr       */
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

static int	init_des(t_cipher_commands *c, t_des_info *info,
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

	if (!init_des(c, &info, cipher, algo))
		return ;
	if (options & MAJ_P)
		print_information(&info, algo);
	while ((cipher->size_buffer = read_fd(cipher->in_fd, cipher->buffer, 8))
	> 0)
	{
		apply_des(cipher, &info, options, algo);
		if (cipher->size_buffer < 8)
			break ;
	}
	if (cipher->size_buffer == 0)
		apply_des(cipher, &info, options, algo);
	if (cipher->size_buffer == -1)
		ft_printf("No such file or directory\n");
}
