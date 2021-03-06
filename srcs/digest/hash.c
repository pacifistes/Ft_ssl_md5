/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:42:36 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/20 14:32:15 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_stdin(char *str)
{
	ft_printf("%s", str);
}

static void	init_hash(t_algo algo, t_hash *hash)
{
	static void (*init[])(t_hash *) = {&init_md5, &init_sha256};

	(*init[algo - 1])(hash);
	ft_bzero(hash->str_block, sizeof(char) * BLOCK_SIZE_CHAR);
	hash->status = 0;
	hash->info.error = 0;
}

t_hash_info	hash_fd(t_algo algo, char *str, char options)
{
	static char	*str_algo[] = {"md5", "sha256"};
	t_hash		hash;
	int			fd;

	fd = (!str) ? 0 : open(str, O_RDONLY);
	init_hash(algo, &hash);
	while (hash.status == 0)
	{
		if ((hash.lenght_str = read_fd(fd, hash.str_block,
		BLOCK_SIZE_CHAR)) == -1 && (hash.info.error = 1) == 1)
		{
			ft_printf("ft_ssl: %s: %s: ", str_algo[algo - 1], str);
			ft_printf("No such file or directory\n");
			break ;
		}
		if (fd == 0 && options & P)
			print_stdin(hash.str_block);
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

t_hash_info	hash_with_null(t_algo algo, char *str, char options, int size)
{
	t_hash hash;

	init_hash(algo, &hash);
	hash.i = 0;
	while (hash.i < size || hash.status == 0)
	{
		hash.lenght_str = 0;
		while (hash.i < size && hash.lenght_str < BLOCK_SIZE_CHAR)
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
