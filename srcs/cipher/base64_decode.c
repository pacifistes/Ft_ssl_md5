/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:32:25 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/13 22:32:30 by bbrunell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	is_valid_char(char c)
{
	static int	terminator = 0;

	if (c == '=')
		terminator = 1;
	else if (!terminator && ft_strchr(BASE64_TABLE, c))
		return (1);
	else
		return (0);
	return (1);
}

static void	init_decode_value(t_decode_base64 *d)
{
	d->size = 0;
	d->i = -1;
	d->h = 0;
}

static void	modify_decode_value(t_decode_base64 *d, int *bit_remaining)
{
	d->h = (d->i != 0 && d->i % 4 == 0) ? d->h + 1 : d->h;
	d->size = (d->i % 4 == 0) ? 0 : 8 - (6 - d->size);
	*bit_remaining = (8 - (6 - d->size));
}

int		decode_block(char *str, char *buffer, int lenght)
{
	t_decode_base64	d;
	int				bit_remaining;
	int				lenght_block;

	lenght_block = 0;
	if (lenght == 0 || lenght % 4 != 0)
		return (0);
	init_decode_value(&d);
	while (++d.i < lenght)
	{
		modify_decode_value(&d, &bit_remaining);
		if (is_valid_char(str[d.i]))
		{
			if (d.i - d.h >= (lenght / 4) * 3)
				continue ;
			d.c = (str[d.i] == '=') ? 0 :
			(bit_extractor((ft_strchr(BASE64_TABLE, str[d.i]) - BASE64_TABLE),
			6 - d.size, 0) << bit_remaining);
			lenght_block = (str[d.i] == '=') ? lenght_block : lenght_block + 1;
			if (is_valid_char(str[d.i + 1]) && str[d.i + 1] != '=')
			{
				d.c |= bit_extractor((ft_strchr(BASE64_TABLE, str[d.i + 1])
				- BASE64_TABLE), bit_remaining, 6 - bit_remaining);
			}
			buffer[d.i - d.h] = d.c;
		}
		else
			return (0);
	}
	return (lenght);
}

void		base64_decode(t_cipher_fd *cipher)
{
	char	buffer[48];
	int		status;

	ft_bzero(buffer, sizeof(char) * 48);
	while ((cipher->size_buffer = read_fd_without_space(cipher->in_fd,
	cipher->buffer, 64)) > 0)
	{
		status = decode_block(cipher->buffer, buffer, cipher->size_buffer);
		if (!status)
			break ;
		else
			write(cipher->out_fd, buffer, (cipher->size_buffer / 4) * 3);
		ft_bzero(buffer, sizeof(char) * 48);
	}
}
