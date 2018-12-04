/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 18:37:26 by bbrunell          #+#    #+#             */
/*   Updated: 2018/12/04 19:57:50 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int bitExtracted(int number, int nbr_bit, int pos)
{
	return ((((1 << nbr_bit) - 1) & (number >> pos)));
}

char		*encode_block(char *str, int lenght)
{
	int		i;
	int		j;
	int		size;
	char	*buffer;

	if (lenght < 1 || lenght > 3)
		return NULL;
	buffer = (char*)malloc(sizeof(char) * 5);
	size = 0;
	i = -1;
	while (++i < 4 && (j = 0) == 0)
	{
		if (i < lenght)
			j = bitExtracted(str[i], (6 - size), 8 - (6 - size));
		if (i > 0 && i <= lenght)
			j |= bitExtracted(str[i - 1], size, 0) << (6 - size);
		else if (i > lenght)
			j = -1;
		buffer[i] = (j < 0) * 61 + (j >= 0) * (j + ('A'
		+ (j > 25) * ('a' - 'Z' - 1) - (j > 51) * ('z' - '0' + 1)
		- (j > 61) * ('9' - '+' + 1) + (j > 62) * '/' - '+' - 1));
		size =  8 - (6 - size);
	}
	buffer[i] = 0;
	return (buffer);
}

void	encode_fd(char *str)
{
	t_encode_base64 b;
	int size;
	int fd;

	fd = (!str) ? 0 : open(str, O_RDONLY);
	size = 0;
	while ((b.lenght_str = read_fd(fd, (char**)&b.str_block, 3)) > 0)
	{
		size += b.lenght_str;
		ft_printf("%s", encode_block(b.str_block, b.lenght_str));
		if (size > 64)
		{
			ft_printf("\n");
			size %= 64;
		}
	}
	if (b.lenght_str == -1)
		ft_printf("Unable to open \'%s\': No such file or directory\n", str);
	ft_printf("\n");
}

char		*decode_block(char *str, int lenght)
{
	char	*buffer;
	int		size;
	int		i;
	int		j;

	buffer = (char*)malloc(sizeof(char) * 4);
	if (lenght != 4)
		return NULL;
	size = 0;
	i = -1;
	while (++i < 3 && (j = 0) == 0)
	{
		if (str[i] == '=')
			buffer[i] = 0;
		else
		{
			buffer[i] = (bitExtracted(str[i], 6 - size, size) << (8 - (6 - size)))
			| bitExtracted(str[i + 1],(8 - (6 - size)), 0);
		}
		size = 8 - (6 - size);
	}
	buffer[i] = 0;
	return (buffer);
}

void	decode_fd(char *str)
{
	t_decode_base64	b;
	int				fd;

	fd = (!str) ? 0 : open(str, O_RDONLY);
	while ((b.lenght_str = read_fd(fd, (char**)&b.str_block, 4)) > 0)
		ft_printf("%s", encode_block(b.str_block, b.lenght_str));
	if (b.lenght_str == -1)
		ft_printf("Unable to open \'%s\': No such file or directory\n", str);
	ft_printf("\n");
}
