/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:13:23 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/11 17:20:00 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"


uint64_t			generate_key(char *password, char *salt)
{
	t_hash_info	info;
	char		*str;

	str = ft_strjoin(password, salt);
	info = hash(MD5, str, 0);
	ft_printf("key = %08x\niv = %08x\n", info.hash[0], info.hash[3]);
	ft_strdel(&str);
	return (0);
}

uint64_t			generate_key_pbkbf(char *password, char *salt)
{
	(void)password;
	(void)salt;
	return (0);
}