/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 14:32:12 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/28 14:37:40 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t	rotr(int n, uint32_t x)
{
	return ((x >> n) | (x << (32 - n)));
}

uint32_t	sigma0(uint32_t x)
{
	return (rotr(7, x) ^ rotr(18, x) ^ (x >> 3));
}

uint32_t	sigma1(uint32_t x)
{
	return (rotr(17, x) ^ rotr(19, x) ^ (x >> 10));
}
