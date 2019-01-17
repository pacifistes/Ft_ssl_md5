/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_encode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:32:36 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/17 16:54:30 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void	encode_block(char *str, char *buffer, int lenght)
{
	int		i;
	int		j;
	int		h;
	int		size;

	if (lenght < 1 || lenght > 48)
		return ;
	size = 0;
	i = -1;
	h = 0;
	while (++i < (((lenght - 1) / 3) + 1) * 4 && (j = 0) == 0)
	{
		size = (i % 4 == 0) ? 0 : 8 - (6 - size);
		h = (i != 0 && i % 4 == 0) ? h + 1 : h;
		if (i - h < lenght)
			j = bit_extractor(str[i - h], (6 - size), 8 - (6 - size));
		if ((i - h % 4) > 0 && i - h <= lenght)
			j |= bit_extractor(str[i - h - 1], size, 0) << (6 - size);
		else if (i - h > lenght)
			j = -1;
		buffer[i] = (j < 0) * 61 + (j >= 0) * (j + ('A'
		+ (j > 25) * ('a' - 'Z' - 1) - (j > 51) * ('z' - '0' + 1)
		- (j > 61) * ('9' - '+' + 1) + (j > 62) * ('/' - '+' - 1)));
	}
}

void		base64_encode(t_cipher_fd *c)
{
	char	buffer[65];
	int		size;

	size = 0;
	ft_bzero(buffer, sizeof(char) * 65);
	while ((c->size_buffer = read_fd(c->in_fd, c->buffer, 48)) > 0)
	{
		size += c->size_buffer;
		if (size > 48)
		{
			ft_putendl_fd("\n", c->out_fd);
			size %= 48;
		}
		encode_block(c->buffer, buffer, c->size_buffer);
		ft_putstr_fd(buffer, c->out_fd);
		ft_bzero(buffer, sizeof(char) * 65);
	}
	ft_putendl_fd(buffer, c->out_fd);
}

void		base64_encode_str(t_cipher_fd *cipher, char *str, int lenght)
{
	char	buffer[65];

	ft_bzero(buffer, sizeof(char) * 65);
	encode_block(str, buffer, lenght);
	ft_putendl_fd(buffer, cipher->out_fd);
}
