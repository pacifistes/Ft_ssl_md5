/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:49:11 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/18 17:46:59 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t	bit_extractor(uint64_t number, uint64_t nbr_bit, uint64_t pos)
{
	return ((((1UL << nbr_bit) - 1) & (number >> pos)));
}

uint32_t	reverse_u32(uint32_t hash)
{
	hash = ((hash & 0x000000FF) << 24) |
	((hash & 0x0000FF00) << 8) |
	((hash & 0x00FF0000) >> 8) |
	((hash & 0xFF000000) >> 24);
	return (hash);
}

uint64_t	reverse_u64(uint64_t hash)
{
	hash = ((hash & 0x00000000000000FF) << 56) |
	((hash & 0x000000000000FF00) << 40) |
	((hash & 0x0000000000FF0000) << 24) |
	((hash & 0x00000000FF000000) << 8) |
	((hash & 0x000000FF00000000) >> 8) |
	((hash & 0x0000FF0000000000) >> 24) |
	((hash & 0x00FF000000000000) >> 40) |
	((hash & 0xFF00000000000000) >> 56);
	return (hash);
}
