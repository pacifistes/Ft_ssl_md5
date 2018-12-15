/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_operator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:49:11 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/14 16:49:48 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint64_t bitExtracted(uint64_t number, uint64_t nbr_bit, uint64_t pos)
{
	return ((((1UL << nbr_bit) - 1) & (number >> pos)));
}