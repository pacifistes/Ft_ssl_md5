/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 17:47:29 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/18 17:00:59 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	print_octet(t_hash_info info, char options, int i)
{
	uint32_t octet;

	if (!ft_strcmp(info.type, "MD5"))
		octet = reverse_u32(info.hash[i]);
	else
		octet = info.hash[i];
	if (options & C)
	{
		ft_printf((i == 0) ? "%02x:%02x:%02x:%02x" : ":%02x:%02x:%02x:%02x",
		((octet & 0xFF000000) >> 24),
		((octet & 0x00FF0000) >> 16),
		((octet & 0x0000FF00) >> 8),
		(octet & 0x000000FF));
	}
	else
		ft_printf("%08x", octet);
}

void		print_hash(t_hash_info info, char *str, int is_file, char options)
{
	int	i;

	i = -1;
	if (str && is_file && !(options & R) && !(options & Q))
		ft_printf("%s(%s)= ", info.type, str);
	if (str && !is_file && !(options & R) && !(options & Q))
		ft_printf("%s(\"%s\")= ", info.type, str);
	while (++i < info.size)
		print_octet(info, options, i);
	if (str && is_file && (options & R) && !(options & Q))
		ft_printf(" %s", str);
	if (str && !is_file && (options & R) && !(options & Q))
		ft_printf(" \"%s\"", str);
	ft_printf("\n");
}
