/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_join.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:10:56 by bbrunell          #+#    #+#             */
/*   Updated: 2017/02/13 15:10:58 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buff_join(char *str, t_buffer *b)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (b->buff >= BUFFER)
		{
			write(1, b->str_buff, BUFFER);
			b->buff = 0;
			b->nbr_write++;
		}
		b->str_buff[b->buff] = str[i];
		b->buff = b->buff + 1;
		i++;
	}
	if (b->buff >= BUFFER)
	{
		write(1, b->str_buff, BUFFER);
		b->buff = 0;
		b->nbr_write++;
	}
}
