/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_des_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 21:40:32 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/17 16:14:00 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_hash_info	create_hash(char *password, uint64_t salt)
{
	int			i;
	t_hash_info	h;
	char		*str;
	int			lenght;

	i = -1;
	lenght = ft_strlen(password) + 9;
	str = (char *)malloc(sizeof(char) * lenght);
	ft_bzero(str, sizeof(char) * lenght);
	ft_strcpy(str, password);
	while (++i < 8)
	{
		((unsigned char *)str)[lenght - 9 + i] =
		((salt >> (56 - (i * 8))) & 0xFF);
	}
	h = hash_with_null(MD5, str, 0, lenght - 1);
	ft_strdel(&str);
	return (h);
}

int			register_key_and_iv(t_cipher_commands *c, t_des_info *info,
t_algo algo)
{
	t_hash_info	h;
	int			status;

	status = 1;
	if (!c->options.password && !c->options.iv && algo == DES_CBC)
	{
		ft_printf("iv undefined\n");
		return (0);
	}
	h = create_hash(c->options.password, info->salt);
	if (!register_hex(c->options.iv, &info->iv,
	((uint64_t)reverse_u32(h.hash[2])) << 32
	| reverse_u32(h.hash[3])))
	{
		ft_printf("invalid hex iv value\n");
		status = 0;
	}
	if (!register_hex(c->options.key, &info->key,
	((uint64_t)reverse_u32(h.hash[0])) << 32
	| reverse_u32(h.hash[1])))
	{
		ft_printf("invalid hex key value\n");
		status = 0;
	}
	return (status);
}

int			init_des_info(t_cipher_commands *c, t_des_info *info, t_algo algo)
{
	char		*verify_pass;

	if (!register_hex(c->options.salt, &info->salt,
	((((uint64_t)rand()) << 32) | rand())))
	{
		ft_printf("invalid hex salt value\n");
		return (0);
	}
	if (!c->options.key || c->options.password)
		info->show_salt = 1;
	if (!c->options.key && !c->options.password)
	{
		c->options.password = getpass("enter encryption password:");
		verify_pass = getpass("Verifying - encryption password:");
		if (ft_strcmp(c->options.password, verify_pass) || !c->options.password)
		{
			if (c->options.password)
				ft_printf("bad password read\n");
			return (0);
		}
	}
	if (!register_key_and_iv(c, info, algo))
		return (0);
	return (1);
}
