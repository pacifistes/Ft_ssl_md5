/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 12:17:42 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/20 12:39:28 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			get_lines(int const fd, char **lines)
{
	int			ret;
	char		*buffer;
	char		*tmp;

	if (fd < 0 || !lines)
		return (-1);
	*lines = ft_strnew(0);
	buffer = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buffer, BUFF_SIZE)) >= 0)
	{
		if (ret == 0)
		{
			if (buffer)
				ft_strdel(&buffer);
			return (0);
		}
		tmp = buffer;
		*lines = ft_strjoin(*lines, buffer);
		ft_strdel(&tmp);
		buffer = ft_strnew(BUFF_SIZE);
	}
	ft_strdel(lines);
	return (-1);
}
