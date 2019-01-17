/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:14:12 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 22:29:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	create_des_block(char *str, int lenght)
{
	int			i;
	int			j;
	uint64_t	block;

	i = -1;
	block = 0;
	while (++i < lenght)
		block |= ((uint64_t)(((unsigned char *)str)[i])) << (56 - 8 * i);
	j = i - 1;
	while (++j < 8)
		block |= ((uint64_t)(8 - (lenght % 8))) << (56 - 8 * j);
	return (block);
}

void		ft_memcpy_uint64(char *str, uint64_t result)
{
	uint64_t reverse;

	reverse = reverse_u64(result);
	ft_memcpy(str, &reverse, 8);
}
