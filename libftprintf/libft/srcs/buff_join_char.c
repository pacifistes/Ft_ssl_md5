/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_join_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:52:31 by bbrunell          #+#    #+#             */
/*   Updated: 2017/03/21 17:52:35 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buff_join_char(char c, t_buffer *b)
{
	if (b->buff >= BUFFER)
	{
		write(1, b->str_buff, BUFFER);
		b->buff = 0;
		b->nbr_write++;
	}
	b->str_buff[b->buff] = c;
	b->buff = b->buff + 1;
	if (b->buff >= BUFFER)
	{
		write(1, b->str_buff, BUFFER);
		b->buff = 0;
		b->nbr_write++;
	}
}
