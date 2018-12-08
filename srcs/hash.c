/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:42:36 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/08 15:58:57 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	init_hash(t_algo algo, t_hash *hash)
{
	static void (*init[])(t_hash *) = {&init_md5, &init_sha256};

	(*init[algo])(hash);
	ft_bzero(hash->str_block, sizeof(char) * BLOCK_SIZE_CHAR);
	hash->status = 0;
	hash->info.error = 0;
}

int			read_fd(t_hash *hash, t_algo algo, char *str, int fd)
{
	static char	*str_algo[] = {"md5", "sha256"};
	char		buffer[64];
	int			size_buffer;
	int			ret;

	size_buffer = 0;
	while (size_buffer < BLOCK_SIZE_CHAR
	&& (ret = read(fd, buffer, BLOCK_SIZE_CHAR - size_buffer)) > 0)
	{
		ft_memcpy(&hash->str_block[size_buffer], &buffer, ret);
		size_buffer += ret;
	}
	hash->lenght_str = size_buffer;
	if (ret == -1 && (hash->info.error = 1) == 1)
	{
		ft_printf("ft_ssl: %s: %s: ", str_algo[algo], str);
		ft_printf("No such file or directory\n");
	}
	return (ret);
}

t_hash_info	hash_fd(t_algo algo, char *str, char options)
{
	t_hash		hash;
	int			fd;

	fd = (!str) ? 0 : open(str, O_RDONLY);
	init_hash(algo, &hash);
	while (hash.status == 0)
	{
		if (read_fd(&hash, algo, str, fd) == -1)
			break ;
		if (fd == 0 && options & P)
			ft_printf("%s", hash.str_block);
		create_block(&hash, options);
		(*hash.apply_algo)(hash.block, &hash.info.hash);
		ft_bzero(hash.str_block, sizeof(char) * BLOCK_SIZE_CHAR);
		if (hash.status == 1)
			break ;
	}
	return (hash.info);
}

t_hash_info	hash(t_algo algo, char *str, char options)
{
	t_hash hash;

	(void)options;
	init_hash(algo, &hash);
	hash.i = 0;
	while (str[hash.i] || hash.status == 0)
	{
		hash.lenght_str = 0;
		while (str[hash.i] && hash.lenght_str < BLOCK_SIZE_CHAR)
		{
			hash.str_block[hash.lenght_str] = str[hash.i];
			hash.i++;
			hash.lenght_str++;
		}
		create_block(&hash, options);
		(*hash.apply_algo)(hash.block, &hash.info.hash);
		ft_bzero(hash.str_block, sizeof(char) * BLOCK_SIZE_CHAR);
	}
	return (hash.info);
}
