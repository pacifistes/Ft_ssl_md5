/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:42:36 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/23 22:50:49 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void init_hash(t_algo algo, t_hash *hash)
{
	void (*init[]) (t_hash *) = {&init_md5, &init_sha256};

	(*init[algo]) (hash);
	ft_bzero(hash->str_block, sizeof(char) * BLOCK_SIZE_CHAR);
	hash->status = 0;
}

t_hash_info			hash_fd(t_algo	algo, char *str, char options)
{
	static char	*str_algo[] = {"md5", "sha256"};
	t_hash	hash;
	int		ret;
	int		fd;

	if (!str)
		fd = 0;
	else
		fd = open(str, O_RDONLY);
	init_hash(algo, &hash);
	hash.status = 0;
	while ((ret = read(fd, hash.str_block, BLOCK_SIZE_CHAR)) >= 0 || hash.status == 0)
	{
		if (fd == 0 && ret != 0 && options & P)
			ft_printf("%s", hash.str_block);
		hash.block = create_block(&hash.status, hash.str_block, ft_strlen(hash.str_block));
		(*hash.apply_algo) (hash.block, &hash.info.hash);
		ft_bzero(hash.str_block, sizeof(char) * BLOCK_SIZE_CHAR);
		free(hash.block);
		if (hash.status == 1)
			break ;
	}
	if (ret == -1)
		ft_printf("ft_ssl: %s: %s: No such file or directory\n", str_algo[algo], str);
	return (hash.info);
}

t_hash_info			hash(t_algo	algo, char *str, char options)
{
	t_hash hash;

	(void)options;
	init_hash(algo, &hash);
	hash.i = 0;
	while (str[hash.i] || hash.status == 0)
	{
		hash.j = 0;
		while (str[hash.i] && hash.j < BLOCK_SIZE_CHAR)
		{
			hash.str_block[hash.j] = str[hash.i];
			hash.i++;
			hash.j++;
		}
		hash.block = create_block(&hash.status, hash.str_block, hash.j);
		ft_printf("%08x\n%08x\n%08x\n%08x\n", hash.info.hash[0], hash.info.hash[1], hash.info.hash[2], hash.info.hash[3]);
		print_block(hash.block, 16);
		(*hash.apply_algo) (hash.block, &hash.info.hash);
		ft_bzero(hash.str_block, sizeof(char) * BLOCK_SIZE_CHAR);
		free(hash.block);
	}
	return (hash.info);	
}