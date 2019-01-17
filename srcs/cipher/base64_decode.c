/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbrunell <bbrunell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:32:25 by bbrunell          #+#    #+#             */
/*   Updated: 2019/01/16 22:21:00 by bbrunell         ###   ########.fr       */
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

char		decode_char(t_decode_base64 *d, char *str, int lenght)
{
	char	c;

	c = 0;
	if (str[d->i] != '=')
	{
		c = (bit_extractor((ft_strchr(BASE64_TABLE, str[d->i]) - BASE64_TABLE),
		d->bit_taken, 0) << d->bit_remaining);
	}
	if (d->i < lenght - 1 && is_valid_char(str[d->i + 1])
	&& str[d->i + 1] != '=')
	{
		c |= bit_extractor((ft_strchr(BASE64_TABLE, str[d->i + 1])
		- BASE64_TABLE), d->bit_remaining, 6 - d->bit_remaining);
	}
	return (c);
}

int			decode_block(char *str, char *buffer, int lenght)
{
	t_decode_base64 d;

	if (lenght == 0 || lenght % 4 != 0)
		return (0);
	ft_bzero(&d, sizeof(t_decode_base64));
	while (d.i < lenght)
	{
		d.nbr_terminator = (str[d.i] == '=') ? d.nbr_terminator + 1
		: d.nbr_terminator;
		if (d.i == lenght - 1)
			break ;
		d.nbr_block = (d.i != 0 && d.i % 4 == 0) ? d.nbr_block + 1
		: d.nbr_block;
		d.bit_taken = (d.i % 4 == 0) ? 6 : 6 - (8 - (d.bit_taken));
		d.bit_remaining = (8 - (d.bit_taken));
		if (!is_valid_char(str[d.i]))
			return (0);
		buffer[d.i - d.nbr_block] = decode_char(&d, str, lenght);
		d.i++;
	}
	return (((d.nbr_block + 1) * 3) - d.nbr_terminator);
}

void		base64_decode(t_cipher_fd *cipher)
{
	char	buffer[48];
	int		size;

	while ((cipher->size_buffer = read_fd_without_space(cipher->in_fd,
	cipher->buffer, 64)) > 0)
	{
		size = decode_block(cipher->buffer, buffer, cipher->size_buffer);
		if (!size)
			break ;
		else
			write(cipher->out_fd, buffer, size);
	}
}
