/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:13:23 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/15 18:18:49 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			generate_key(t_cipher_commands *c, t_des_info *info)
{
	t_hash_info	hash_info;
	char		*str;
	int			lenght;
	int			i;

	i = 0;
	lenght = ft_strlen(c->options.password) + 9;
	str = (char *)malloc(sizeof(char) * lenght);
	ft_bzero(str, sizeof(char) *  lenght);
	ft_strcpy(str, c->options.password);
	while (i < 8)
	{
		((unsigned char *)str)[lenght - 9 + i] = ((info->salt >> (56 - (i * 8))) & 0xFF);
		i++;
	}
	ft_printf("str = [%s]\n", str);
	ft_printf("str = [%016llx]\n", info->salt);
	hash_info = hash_with_null(MD5, str, 0, lenght - 1);
	ft_strdel(&str);
	for (int j=0;j<4;j++){ft_printf("%08x\n", hash_info.hash[j]);}
	if (!c->options.key)
		info->key = ((uint64_t)reverse_u32(hash_info.hash[0])) << 32 | reverse_u32(hash_info.hash[1]);
	if (!c->options.iv)
		info->iv = ((uint64_t)reverse_u32(hash_info.hash[2])) << 32 | reverse_u32(hash_info.hash[3]);
}

uint64_t			generate_key_pbkbf(char *password, char *salt)
{
	(void)password;
	(void)salt;
	return (0);
}

uint64_t			generate_salt()
{
	static int	is_rand_set = 0;
		
	if (is_rand_set == 0)
	{
		srand(time(NULL));
		is_rand_set = 1;
	}
	return (((uint64_t)rand()) | (((uint64_t)rand()) << 32));
}