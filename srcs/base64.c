/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:37:26 by bbrunell          #+#    #+#             */
/*   Updated: 2018/11/28 19:49:14 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char		*encode_block(char *str, int lenght)
{
	static char	tab[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	char *buffer;
	buffer = (char*)malloc(sizeof(char) * 5);
	if (lenght < 1 || lenght > 3)
		return NULL;
	if (lenght == 3)
	{
		buffer[0] = tab[bitExtracted(str[0], 6, 2)];
		buffer[1] = tab[(bitExtracted(str[0], 2, 0) << 4) | bitExtracted(str[1], 4, 4)];
		buffer[2] = tab[(bitExtracted(str[1], 4, 0) << 2) | bitExtracted(str[2], 2, 6)];
		buffer[3] = tab[bitExtracted(str[2], 6, 0)];
		buffer[4] = 0;
		return (buffer);
	}
	if (lenght == 2)
	{
		buffer[0] = tab[bitExtracted(str[0], 6, 2)];
		buffer[1] = tab[(bitExtracted(str[0], 2, 0) << 4) | bitExtracted(str[1], 4, 4)];
		buffer[2] = tab[(bitExtracted(str[1], 4, 0) << 2)];
		buffer[3] = '=';
		buffer[4] = 0;
		return (buffer);
	}
	if (lenght == 1)
	{
		buffer[0] = tab[bitExtracted(str[0], 6, 2)];
		buffer[1] = tab[(bitExtracted(str[0], 2, 0) << 4)];
		buffer[2] = '=';
		buffer[3] = '=';
		buffer[4] = 0;
		return (buffer);
	}
	return NULL;
}

void	encode_fd(char *str)
{
	t_encode_base64 b;
	int fd;

	fd = (!str) ? 0 : open(str, O_RDONLY);
	while ((b.lenght_str = read_fd(fd, &b.str_block, 4)) > 0)
		ft_printf("%s", encode_block(b.str_block, b.lenght_str));
	if (b.lenght_str == -1)
		ft_printf("Unable to open \'%s\': No such file or directory\n", str);
	ft_printf("\n");
}

char		*decode_block(char *str, int lenght)
{
	char *buffer;
	int i;
	buffer = (char*)malloc(sizeof(char) * 4);
	if (lenght != 4)
		return NULL;
	buffer[3] = 0;
	buffer[0] = (str[0] << 2) | bitExtracted(str[1], 2, 0);
	buffer[1] = (bitExtracted(str[1], 4, 2) << 2 | ;
	buffer[2] = ;
}