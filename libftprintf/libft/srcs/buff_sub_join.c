/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_sub_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:52:52 by bbrunell          #+#    #+#             */
/*   Updated: 2017/03/21 17:52:55 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buff_sub_join(const char *str, t_buffer *b, int i, int len)
{
	int j;

	j = 0;
	while (str && str[i] && j < len)
	{
		if (b->buff == BUFFER)
		{
			write(1, b->str_buff, b->buff);
			b->buff = 0;
			b->nbr_write++;
		}
		b->str_buff[b->buff] = str[i];
		b->buff = b->buff + 1;
		i++;
		j++;
	}
	if (b->buff >= BUFFER)
	{
		write(1, b->str_buff, BUFFER);
		b->buff = 0;
		b->nbr_write++;
	}
}
