/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 16:47:20 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 21:53:49 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int			read_fd_without_space(int fd, char *dest, int size)
{
	char		buffer[size];
	int			size_buffer;
	int			ret;
	int			counter;
	int			i;

	size_buffer = 0;
	while (size_buffer < size
	&& (ret = read(fd, buffer, size - size_buffer)) > 0)
	{
		i = 0;
		counter = 0;
		while (i < ret)
		{
			if ((buffer[i] != ' ' && buffer[i] != '\n' && buffer[i] != '\v'
			&& buffer[i] != '\f' && buffer[i] != '\t' && buffer[i] != '\r'))
			{
				dest[size_buffer + counter] = buffer[i];
				counter++;
			}
			i++;
		}
		size_buffer += counter;
	}
	return ((ret == -1) ? ret : size_buffer);
}

int			read_fd(int fd, char *dest, int size)
{
	char		buffer[size];
	int			size_buffer;
	int			ret;

	size_buffer = 0;
	while (size_buffer < size
	&& (ret = read(fd, buffer, size - size_buffer)) > 0)
	{
		ft_memcpy(&dest[size_buffer], &buffer, ret);
		size_buffer += ret;
	}
	return ((ret == -1) ? ret : size_buffer);
}
